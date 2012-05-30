
import sys

class Message:
	def __init__:
		self.translated = ""
		self.state = 

	def append(self, char):
		if (char == '['):
			self.translated += "msg("
		self.translated += char

def process(file):
	for line in file:
		print line

def main():
	if len(sys.argv) != 3:
		raise SystemExit("Invalid arguments")
	if sys.argv[1] == "-f":
		file = open(sys.argv[2])
		process(file)

if __name__ == "__main__":
    main()