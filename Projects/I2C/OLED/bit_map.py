from PIL import Image

# Load the image
image = Image.open("/home/shrey_shah/Downloads/yami.png").convert('1')  # Convert to 1-bit monochrome

# Resize to 128x64 (SSD1306 resolution)
image = image.resize((128, 64))

# Function to convert image to SSD1306 bitmap (Page Addressing Mode)
def image_to_ssd1306_bitmap(image):
    width, height = image.size
    pages = height // 8  # Number of pages (8 rows per page)
    bitmap = []

    for page in range(pages):
        for x in range(width):
            byte = 0
            for y in range(8):
                pixel = image.getpixel((x, page * 8 + y))
                if pixel == 0:  # Assuming black is 0
                    byte |= 1 << y
            bitmap.append(byte)
    
    return bitmap

# Get the bitmap
bitmap = image_to_ssd1306_bitmap(image)

# Print the bitmap in C array format (128x8 pages = 1024 bytes)
print("const unsigned char bitmap[1024] = {")
for i, byte in enumerate(bitmap):
    if i % 16 == 0:
        print("    ", end="")
    print(f"0x{byte:02X}, ", end="")
    if i % 16 == 15:
        print()
print("};")