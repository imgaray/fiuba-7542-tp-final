
all: install

install: install_agente install_cliente install_servidor

install_agente:
	mkdir apAgente
	cd agente; make
	cp agente/main apAgente
	cp agente/*.conf apAgente
	cp agente/*.config apAgente
	
install_cliente:
	mkdir apCliente
	cd cliente; make
	cp -f cliente/main apCliente
	cp -f cliente/*.conf apCliente
	cp -f cliente/*.config apCliente
	cp -f cliente/Vista/*.glade apCliente

install_servidor:
	mkdir apServidor
	cd servidor; make
	cp -f servidor/main apServidor
	cp -f servidor/*.conf apServidor
	cp -f servidor/*.config apServidor
	cp -f servidor/*.dat


uninstall:
	$(shell rm -f -r $(wildcard apCliente))
	$(shell rm -f -r $(wildcard apServidor))
	$(shell rm -f -r $(wildcard apAgente))

doc:
	

.PHONY: all install	install_agente install_cliente install_servidor	uninstall doc
