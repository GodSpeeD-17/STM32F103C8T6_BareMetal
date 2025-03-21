import argparse
from PIL import Image

# Parse arguments from the command line
parser = argparse.ArgumentParser(description="Generate and update bitmap based on the selected image.")
parser.add_argument('--image', type=str, required=True, help="Specify the image to use.")
args = parser.parse_args()

print(f"\n{args.image}\n")

# Set the image path based on the command line argument
if args.image == "yami":
    image_path = "./Images/yami.png"
    threshold = 70
elif args.image == "gojo":
    image_path = "./Images/gojo.png"
    threshold = 128
# Set a default image if no yami bitmap is found
else:
    image_path = "./Images/family.png"
    threshold = 158

# Open and process the image
try:
    img = Image.open(image_path)
    print(f"Loaded image: {image_path}")
    # Add your image processing code here...
except Exception as e:
    print(f"Error opening image: {e}")


# Replace with your desired output file path
output_file = "./Inc/main.h"  
# The variable name you want to overwrite
variable_name = "static const uint8_t image_bitmap[1024]"

# Function to convert image to SSD1306 bitmap (Page Addressing Mode)
def image_to_ssd1306_bitmap(image, threshold=128):
	width, height = image.size
	pages = (height + 7) // 8  # Number of pages (8 rows per page)

	bitmap = []

	for page in range(pages):
		for x in range(width):
			byte = 0
			for y in range(8):
				pixel_y = page * 8 + y
				if pixel_y < height:  # Check if within image bounds
					pixel = image.getpixel((x, pixel_y))
					if isinstance(pixel, tuple):  # Convert color to grayscale
						pixel = int(0.299 * pixel[0] + 0.587 * pixel[1] + 0.114 * pixel[2])
					# Apply threshold to convert grayscale to black/white
					if pixel < threshold:  # Black pixel
						byte |= (1 << y)
			bitmap.append(byte)
	
	return bitmap

# Function to overwrite the bitmap array in the file
def overwrite_variable_in_file(bitmap, file_path, variable_name):
	with open(file_path, 'r+') as f:
		lines = f.readlines()

		# Find the line containing the variable_name and remove the old bitmap data
		start_index = None
		end_index = None
		
		for i, line in enumerate(lines):
			if variable_name in line:
				start_index = i
				break
		
		if start_index is not None:
			# Find the end of the variable definition
			for j in range(start_index + 1, len(lines)):
				if '};' in lines[j]:
					end_index = j
					break

			# Replace the old variable with the new bitmap data
			if end_index is not None:
				new_lines = lines[:start_index + 1]
				new_lines.append('= {\n')
				for i, byte in enumerate(bitmap):
					if(i == 0):
						new_lines.append("\t")
					elif (i + 1) % 16 == 0:
						new_lines.append("\n\t")
					new_lines.append(f"0x{byte:02X}, ")
				new_lines.append("\n};\n")
				new_lines.extend(lines[end_index + 1:])

				# Rewrite the file with the new bitmap data
				f.seek(0)
				f.writelines(new_lines)
				f.truncate()

# Main function
def generate_bitmap(image_path, threshold=128, output_file="output.txt", variable_name="static const uint8_t yami_bitmap[1024]"):
	# Load the image
	image = Image.open(image_path)

	# Resize the image to fit 128x64 resolution (maintaining aspect ratio)
	image.thumbnail((128, 64), Image.Resampling.LANCZOS)
	width, height = image.size

	# Create a new blank image with 128x64 resolution
	new_image = Image.new("L", (128, 64), 255)  # White background
	# Paste the resized image onto the center of the blank image
	new_image.paste(image, ((128 - width) // 2, (64 - height) // 2))

	# Convert the image to SSD1306 bitmap
	bitmap = image_to_ssd1306_bitmap(new_image, threshold)

	# Overwrite the bitmap array in the specified file
	overwrite_variable_in_file(bitmap, output_file, variable_name)

	print(f"Bitmap written and variable {variable_name} overwritten in {output_file}")

# Generate the bitmap and overwrite the variable in the file
generate_bitmap(image_path, threshold, output_file, variable_name)
