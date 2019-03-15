from PIL import Image

im = Image.open('toolbar.jpg', 'r')
pix_val = list(im.getdata())
pix_val_flat = [x for sets in pix_val for x in sets]

print(im.size)

file = open('toolbar.txt','w')
file.write(str(im.size[0]))
file.write(" ")
file.write(str(im.size[1]))
file.write("\n")
for (r, g, b) in pix_val:
	file.write(str(r))
	file.write(" ")
	file.write(str(g))
	file.write(" ")
	file.write(str(b))
	file.write("\n")