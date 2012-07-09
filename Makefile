MSJ_AGENTE = @echo "::::::Instalando Agente::::::"
MSJ_CLIENTE = @echo "::::::Instalando Cliente::::::"
MSJ_SERV = @echo "::::::Instalando Servidor::::::"

MSJ_ESP = @echo "..."

MSJ_DESINS = @echo "Desinstalando "

MSJ_DOCS = @echo "Generando documentacion..."


all: install

install: uninstall doc install_agente install_cliente install_servidor

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
	$(MSJ_ESP);cp -f cliente/*.glade apCliente
	$(MSJ_ESP);cp -f cliente/*.xml apCliente
	$(MSJ_ESP);cp -f cliente/*.png apCliente 
	

install_servidor:
	$(MSJ_SERV); mkdir apServidor
	$(MSJ_ESP);cd servidor; make --no-print-directory -s
	$(MSJ_ESP);cp -f servidor/main apServidor
	$(MSJ_ESP);cp -f servidor/*.conf apServidor
	$(MSJ_ESP);cp -f servidor/*.config apServidor
	$(MSJ_ESP);cp -f servidor/*.dat apServidor

doc:
	$(MSJ_DOCS); doxygen doxyConfig


debug:
	rm -r -f DEBUG_RELEASE
	mkdir DEBUG_RELEASE
	cd agente; make DEBUG=yes
	mkdir DEBUG_RELEASE/agente
	cp agente/main DEBUG_RELEASE/agente
	cp agente/*.conf DEBUG_RELEASE/agente
	cp agente/*.config DEBUG_RELEASE/agente
	cd servidor; make DEBUG=yes
	mkdir DEBUG_RELEASE/servidor
	cp -f servidor/main DEBUG_RELEASE/servidor
	cp -f servidor/*.conf DEBUG_RELEASE/servidor
	cp -f servidor/*.config DEBUG_RELEASE/servidor
	cp -f servidor/*.dat DEBUG_RELEASE/servidor
	mkdir DEBUG_RELEASE/cliente 
	cd cliente; make DEBUG=yes 
	cp -f cliente/main DEBUG_RELEASE/cliente 
	cp -f cliente/*.conf DEBUG_RELEASE/cliente 
	cp -f cliente/*.config DEBUG_RELEASE/cliente
	cp -f cliente/*.glade DEBUG_RELEASE/cliente
	cp -f cliente/*.png DEBUG_RELEASE/cliente
	cp -f cliente/*.xml DEBUG_RELEASE/cliente 
	
	 	
uninstall:
	$(MSJ_DESINS)
	$(MSJ_ESP);rm -f -r apCliente 
	$(MSJ_ESP);rm -f -r apServidor
	$(MSJ_ESP);rm -f -r apAgente
	$(MSJ_ESP);rm -f -r docs
	$(MSJ_ESP);rm -f -r DEBUG_RELEASE


.PHONY: all install	install_agente install_cliente install_servidor	uninstall debug doc
