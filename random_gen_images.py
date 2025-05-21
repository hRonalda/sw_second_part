import sys
import random
import os

index = int(sys.argv[1])
output_dir = "random_images"
width, height = 100, 100

os.makedirs(output_dir, exist_ok=True)
filename = os.path.join(output_dir, f"random_image_{index+1}.ppm")

with open(filename, "w") as f:
    f.write("P3\n")
    f.write(f"{width} {height}\n")
    f.write("255\n")
    for _ in range(height):
        row = []
        for _ in range(width):
            r = random.randint(0, 255)
            g = random.randint(0, 255)
            b = random.randint(0, 255)
            row.extend([str(r), str(g), str(b)])
        f.write(" ".join(row) + "\n")
