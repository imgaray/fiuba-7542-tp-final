import sys

ignorados = ['*','/']
marcador_comienzo = "@DOC"
marcador_fin = "@END"

def main():
	if (len(sys.argv) < 2):
		print "faltan argumentos al programa"
	archivos = sys.argv[1:]
	print archivos
	for archivo in archivos:
		try:
			salida = open("Documentacion" + archivo + ".txt", 'w')
			entrada = open(archivo)
			debeProcesar = False
			output = ""
			for linea in entrada:
				print linea
				if marcador_comienzo in linea:
					debeProcesar = True
					continue
				if marcador_fin in linea:
					debeProcesar = False
					continue
				if debeProcesar:
					print linea
					for caracter in ignorados:
						linea = linea.replace(caracter, "")
					output += linea
			output += "\n"
			salida.write(output)
			salida.close()
		except IOError as e:
			print "IOError({0}): {1} ".format(e.errno, e.strerror)
	return 0

if __name__ == '__main__':
	main()

