#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

def main():
	if (len(sys.argv) < 2):
		print "faltan argumentos al programa"
		return 1
	archivos = sys.argv[1:]
	output = ""
	i = 0
	encabezado = "Seccion {}"
	try:
		salida = open("Documentacion.txt", 'w')
		for archivo in archivos:
			entrada = open(archivo)
			output += encabezado.format(++i)
			for linea in entrada:
				output += linea
			output += '\n'
		salida.write(output)
		salida.close()
	except IOError as e:
		print "IOError({0}): {1} ".format(e.errno, e.strerror)
	return 0

if __name__ == '__main__':
	main()

