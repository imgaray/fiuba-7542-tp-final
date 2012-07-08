/*
 * Pruebas.h
 *
 *  Created on: 03/06/2012
 *      Author: migue
 */

#ifndef PRUEBAS_H_
#define PRUEBAS_H_

/**
 * @brief test que comprueba que se carga bien desde un archivo
 * el modelo de datos, comprobando que las dimensiones y hechos
 * sean los correctos segun cada modelo, y tambien que su cantidad sea correcta.
 * comprobando ademas si existe la dimension especial "Fecha" para tratarla
 * de forma diferente segun el lugar donde se utilice.
 */
void testOrganizacion();

/**
 * @brief test que comprueba que se almacene bien cualquier tipo de registro
 * en el ArchivoDeDatos y que se puedan recuperar correctamente, y que entregue
 * correctamente tambien la cantidad de registros almacenados.
 */
void testArchivoDeDatos();

/**
 * @brief test que comprueba que se realice correctamente la interseccion para
 * dos listas de ids.
 */
void testInterseccion();

/**
 * @brief test para probar el funcionamiento de una utilidad, la de generar registros aleatorios
 * para la base de datos.
 */
void testGeneradorRegistros();

/**
 * @brief test que comprueba que este bien formada, que sus atributos concuerden con
 * la organizacion del servidor y no tenga consulta que sean invalidas o parametros
 * que no concuerden para la correcta resolucion de una consulta de cliente
 */
void testValidadorConsulta();

/**
 * @brief test que comprueba que las consultas sean realizadas por un agente potencial
 * sean correctas y esten bien formadas.
 */
void testValidadorEntrada();

/**
 * @brief test extenso para la base de datos que carga una organziacion tipica y se almacenan algunos
 * registros en esta para hacer diferentes tipos de consultas, con filtros y/o entradas y con resultados.
 *  Se comprueba que se generen correctamente las tablas normales y las pivote. Se prueba tambien que
 *  todos los tipos de agregacion sean realizados correctamente. Ademas se realizan salidas por pantalla
 *  de las consulta resueltas.
 */
void testBaseDeDatos();

/**
 * @brief test similar a testSeparador() pero con la diferencia de que el metodo separar(...)
 * se comprueba con mas datos muchos mas extensos.
 */
void testPesadoSeparador();

/**
 * @brief Prueba el funcionamiento de uno los metodos mas usado que es el separador(..)
 * perteneciente a la clase Utilitario. Se realizan pruebas sencillas de separar
 * strings cortos.
 */
void testSeparador();

/**
 * @brief este test prueba el funcionamiento de los indices utilizados en la base de
 * datos para filtrar los registros. El test se hace con enteros ya que la clase
 * Indice es un template
 */
void testIndice();

/**
 * @brief se comprueba que se serialicen y deserilacen bien las consulta, que se guardan
 * y recuperen correctamente los filtros, entradas, resultados, grupo X de la Tabla
 * Pivote y grupo Y de la Tabla Pivote.
 */
void testConsulta();

/**
 * @brief similar al test de consulta, se comprueba que se serialicen y deserialicen
 * correctamente las respuestas, tambien que se guardan bien y se puedan recuperar
 * bien sus atributos.
 */
void testRespuesta();

/**
 * @brief test que comprueba el buen funcionamiento del manejador de fechas, mostrando
 * como serian las fechas compuestas, y comprobando que correspondan bien todos los
 * tipos de rango cuando se descomponen en dos fechas como intervalo.
 */
void testMFechas();

/**
 * @brief  test que comprueba que se almacen bien y se recuperen correctamente los id
 * de registros para una fecha o un rango de fechas.
 */
void testIndFechas();

/**
 * @brief test que se realiza a una base de datos real,que es una copia de la que
 * realmente se va a usar, resolviendo consultas mas reales que el test anterior
 * de base de datos. Ademas mostrando salidas por pantalla de las consueltas resueltas.
 */
void testBaseDeDatosReal();



#endif /* PRUEBAS_H_ */
