import os

SOURCE_TYPES = (
	".h",
)

def make_header(a_directories):
	tmp = []
	for directory in a_directories:
		for root, dirs, files in os.walk(directory):
			for file in files:
				if file.endswith(SOURCE_TYPES):
					if not file.startswith("Starfield"):
						path = os.path.join(root, file)
						tmp.append(os.path.normpath(path))

	sources_tmp = []
	for file in tmp:
		sources_tmp.append(file.replace("\\", "/"))
	
	sources = []
	for source in sources_tmp:
		sources.append(source.replace("include/", ""))		
	
	sources.sort()

	out = open(os.path.join("include/RE", "Starfield.h"), "w")
	out.write("#pragma once\n")
	out.write("\n")
	out.write("#include \"SFSE/Impl/PCH.h\"\n")
	out.write("\n")
	for source in sources:
		out.write("#include \"{}\"\n".format(source))

def main():
	cur = os.path.dirname(os.path.realpath(__file__))
	os.chdir(cur + "/..")
	make_header([ "include/RE" ])
	

if __name__ == "__main__":
	main()
