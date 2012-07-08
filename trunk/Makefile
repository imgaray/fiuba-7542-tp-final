MSJ_AGENTE = @echo "::::::Instalando Agente::::::"
MSJ_CLIENTE = @echo "::::::Instalando Cliente::::::"
MSJ_SERV = @echo "::::::Instalando Servidor::::::"

MSJ_ESP = @echo "..."

MSJ_DESINS = @echo "Desinstalando "


all: install

install: install_agente install_cliente install_servidor

install_agente:
	$(MSJ_AGENTE);mkdir apAgente
	$(MSJ_ESP);cd agente; make --no-print-directory -s
	$(MSJ_ESP);cp agente/main apAgente
	$(MSJ_ESP);cp agente/*.conf apAgente
	$(MSJ_ESP);cp agente/*.config apAgente
	
install_cliente:
	$(MSJ_CLIENTE);mkdir apCliente
	$(MSJ_ESP);cd cliente; make --no-print-directory -s
	$(MSJ_ESP);cp -f cliente/main apCliente
	$(MSJ_ESP);cp -f cliente/*.conf apCliente
	$(MSJ_ESP);cp -f cliente/*.config apCliente
	$(MSJ_ESP);mkdir apCliente/Vista
	cp -f cliente/Vista/*.glade apCliente/Vista

install_servidor:
	$(MSJ_SERV); mkdir apServidor
	$(MSJ_ESP);cd servidor; make --no-print-directory -s
	$(MSJ_ESP);cp -f servidor/main apServidor
	$(MSJ_ESP);cp -f servidor/*.conf apServidor
	$(MSJ_ESP);cp -f servidor/*.config apServidor
	$(MSJ_ESP);cp -f servidor/*.dat apServidor


uninstall:
	$(MSJ_DESINS)
	$(MSJ_ESP);rm -f -r apCliente
	$(MSJ_ESP);rm -f -r apServidor
	$(MSJ_ESP);rm -f -r apAgente
	
doc:

.PHONY: all install	install_agente install_cliente install_servidor	uninstall doc
