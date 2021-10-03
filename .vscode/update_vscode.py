import json
import pathlib
from collections import OrderedDict

include_dirs = [
	r"${workspaceFolder}/**",
	r"/opt/llvm/include/c++/v1/**"
]

defines = []

vscode_dir = pathlib.Path(__file__).parent.absolute()
root_dir = vscode_dir.parent
	
with open(root_dir / 'build' / 'conanbuildinfo.txt', 'r') as f:
	is_include_dir = False
	is_define = False
	for line in f:
		line = line.strip()
		if line.startswith('[') and line.endswith(']'):
			is_include_dir = False
			is_define = False
			if line == '[includedirs]':
				is_include_dir = True
			elif line == '[defines]':
				is_define = True
			continue
		if line == '':
			continue
		if is_include_dir:
			include_dirs.append(line)
		if is_define:
			defines.append(line)

with open(vscode_dir / 'c_cpp_properties.json', 'r+') as f:
	root = json.loads(f.read(), object_pairs_hook=OrderedDict)
	root['configurations'][0]['includePath'] = include_dirs
	root['configurations'][0]['defines'] = defines
	new_content = json.dumps(root, indent=4)
	f.seek(0)
	f.write(new_content)
	f.truncate()

# print("Include dirs: ")
# print(include_dirs)
# print("Defines: ")
# print(defines)