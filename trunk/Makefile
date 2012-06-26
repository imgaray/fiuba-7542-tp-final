
all: install

install: install_agente install_cliente install_servidor

install_agente:
	mkdir apAgente
	cd agente; make
	cp agente/main apAgente
	cp agente/*.conf apAgente
install_cliente:
	mkdir apCliente
	cd cliente; make
	cp cliente/main apCliente
	cp cliente/*.conf apCliente

install_servidor:
	mkdir apServidor
	cd servidor; make
	cp servidor/main apServidor
	cp servidor/*.conf apServidor
	
uninstall:
	$(shell rm -f -r $(wildcard apCliente))
	$(shell rm -f -r $(wildcard apServidor))
	$(shell rm -f -r $(wildcard apAgente))

.PHONY: all install	install_agente install_cliente install_servidor	uninstall
