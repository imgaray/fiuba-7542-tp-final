SUBDIRS = agente cliente servidor

EXTRA = comun

all: install

install: agente cliente servidor
		
agente:
	$(shell make -C agenet)
	$(shell mkdir apAgente)
	$(shell mv agente/main apAgente)
	$(shell mv agente/*conf apAgente)

cliente:
	$(shell make -C cliente)
	$(shell mkdir apCliente)
	$(shell mv cliente/main apCliente)
	$(shell mv cliente/*conf apCliente)

servidor:
	$(shell make -C servidor)
	$(shell mkdir apServidor)
	$(shell mv servidor/main apServidor)
	$(shell mv servidor/*conf apServidor)

.PHONY: install all		
