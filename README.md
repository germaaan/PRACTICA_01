# Práctica 1: Creación y despliegue de una aplicación en un PaaS
# German Martinez Maldonado
# Publicado bajo licencia GNU GENERAL PUBLIC LICENSE Version 3

El PaaS sobre el que voy a desplegar la práctica es OpenShift, plataforma que ya he usado en uno de los ejercicios anteriores. El motivo de seleccionar este PaaS es entre otros, que es un plataforma muy extendida y que soporta PHP, algo imprescindible para la aplicación a desplegar.

La licencia bajo la que se publica la aplicación es GNU GPL v3, lo que permite realizar modificaciones sobre la misma, realizar copias y distribuirlas, tanto de esta versión como de cualquier versión modificada, pudiendo cobrar o no por la distribución de dichas copias. OpenShift está publicado bajo una licencia Apache License 2.0, pero nos permite su uso con proyectos bajo licencia GNU GPL v3.

La aplicación está desarrollada en PHP, está compuesta por un formulario en el que al introducir el identificador de un alumno de la asignatura "Infraestructura Virtual" y procesarlo, obtenemos variada información sobre ese alumno: enlace a su repositorio de GitHub, nombre, apellidos, dirección de correo electrónico y dirección de cuenta en Twitter; además también tenemos un enlace a una página con todos los identificadores de los alumnos listados para poder acceder directamente a la información citada. Así es como queda la aplicación final:

![practica01_prueba1](https://dl.dropboxusercontent.com/s/omc8ckuqbrd0d00/prueba1.png)
![practica01_prueba2](https://dl.dropboxusercontent.com/s/zh35p8lpnfqic9s/prueba2.png)

Lo primero que necesitaremos es una cuenta en OpenShift, algo que ya creamos en el ejercicio 13. Seguidamente  para poder trabajar en línea de comandos desde nuestro terminal, debemos instalar los paquetes `rubygems` y `git`, y además instalar la aplicación cliente `rhc` con `gem` y actualizarlo a su última versión:

```
sudo apt-get install rubygems git
sudo gem install rhc
gem update rhc
```

Una vez instalada la herramienta de cliente, deberemos configurarla con `rhc setup`, lo que nos pedirá la información que se ve en la imagen y hará varias comprobaciones: 

![practica01_img01](https://dl.dropboxusercontent.com/s/t6aju2n4bub4o4z/practica01_img01.png)

Ha llegado el momento de crear la aplicación, para la creación de nuestra aplicación podemos usar un gran cantidad de frameworks de los que nos provee OpenShift (los podemos listar con `rhc cartridge list`. Como inicio, vamos a indicar que nuestra aplicación va a usar PHP, por lo que introduciremos `rhc app create acceso php-5.3` ("acceso" es el nombre de nuestra aplicación):

![practica01_img02](https://dl.dropboxusercontent.com/s/9609c8jitliiqis/practica01_img02.png)

Añadimos el gestor de base de datos a nuestra aplicación con `rhc cartridge add mysql-5.1 -a acceso`:

![practica01_img04](https://dl.dropboxusercontent.com/s/wb5bycqo3mtbtkw/practica01_img04.png)

Si tenemos que cambiar la configuración de acceso a la base de datos de nuestra aplicación podemos acceder al mecanismo de nuestra aplicación mediante `ssh`, lo haremos con `rhc app ssh -a acceso`. Para simplificar la gestión de la base de datos, vamos a añadir también a nuestra aplicación `phpMyAdmin` (`rhc cartridge add phpmyadmin-4 -a acceso`):

![practica01_img07](https://dl.dropboxusercontent.com/s/6l9u0vkl00r23d8/practica01_img07.png)

Una vez que hemos terminado con la configuración de las herramientas, vamos a comenzar a desarrollar la aplicación, al ser una aplicación PHP que obtendrá sus datos de una base de datos MySql, lo que haremos primero es introducir la información en la base de datos, para ello nos ayudaremos de la aplicación `phpMyAdmin` a la que podemos acceder desde la dirección "http://acceso-germaaan.rhcloud.com/phpmyadmin", aunque sin el nombre de usuario y contraseña no se puede acceder.

Con la información introducida en la base de datos, ahora debemos configurar la conexión de la aplicación con la base de datos, aunque vamos a liberar de forma pública el código de nuestra aplicación, no nos interesa que los aspectos privados de acceso a la base de datos se compartan, por lo que crearemos un archivo de configuración externo. Para conocer los valores que tenemos que usar para realizar la conexión, primero deberemos conectarnos mediante SSH a nuestro repositorio en OpenShift; para conectarnos mediante SSH usamos `rhc app ssh -a acceso` (siendo "acceso" el nombre de nuestra aplicación), y para conocer los valores de las variables del entorno necesarias usamos `env | grep OPENSHIT`.

![practica01_ssh](https://dl.dropboxusercontent.com/s/t9kf6lu7qdkpnf0/ssh.png)

No mostramos el resultado el comando `env | grep OPENSHIFT` por motivos de seguridad, pero lo que si vemos en la imagen es una estructura de carpetas, para que nuestro fichero de configuración queda fuera de la parte pública, lo crearemos dentro de la carpeta "mysql" y le vamos a dar el nombre "configuracion.inc", con un contenido similar al siguiente pero con los valores obtenidos de las variables del entorno:

* DIRECCION_IP_SERVIDOR: $OPENSHIFT_MYSQL_DB_HOST
* PUERTO: $OPENSHIFT_MYSQL_DB_PORT
* NOMBRE_BASE_DATOS: $OPENSHIFT_GEAR_NAME
* USUARIO: $OPENSHIFT_MYSQL_DB_USERNAME
* CONTRASEÑA: $OPENSHIFT_MYSQL_PASSWORD
* NOMBRE_TABLA: Será el nombre de la tabla que hayamos creado en nuestra base de datos

```
<?php
     	define("DB_DSN","mysql:host=DIRECCION_IP_SERVIDOR;port=PUERTO;dbname=NOMBRE_BASE_DATOS");
        define("DB_USUARIO","USUARIO");
        define("DB_PASS","CONTRASEÑA");
        define("TABLA_ALUMNOS","NOMBRE_TABLA");
?>
```

Ya solo nos quedaría hacer la aplicación propiamente dicha, en la plataforma OpenShift, el código de las aplicaciones debe estar situado en "~/app-root/repo/" y en nuestro caso, por ser una aplicación PHP, dentro del directorio "repo" en el directorio "php". En ese directorio, podemos encontrar archivos por defecto como "index.php", que será el índice de nuestro dominio y que en nuestro caso será el que contenga el formulario.

Además crearemos otros archivos "php", "listado.php" que contendrá el listado de los identificadores de los alumnos, y "acceso.php" que será la página que muestre la información del alumno en función del identificador recibido mediante un paso de valor GET, para poder usarlo tanto para el formulario como para los enlaces. Hemos añadido también un "index.css" simplemente para cambiarle algo el aspecto predefinido de las aplicaciones creadas en OpenShift. 

Sin embargo, donde realmente está la importancia es en el archivo "Alumno.class.inc", que será el archivo que contenga definida la clase "Alumno", clase que cuenta con todos los métodos necesarios para conectarse a la base de datos, buscar la información de un alumno y formatear como será mostrada por pantalla; es la parte más importante de la aplicación, la que le da toda la funcionalidad a la misma.

Una vez tenemos la aplicación funcionando en OpenShift, para poder subirlo a GitHub lo primero que tenemos que hacer es clonar el proyecto, para lo que necesitaremos la dirección SSH, que podemos obtener desde la página de gestión de nuestra aplicación en la página de OpenShift. En nuestro caso debemos usar la orden `git clone ssh://525c7ef35004461e1f00009d@acceso-germaaan.rhcloud.com/~/git/acceso.git/`.

![practica01_clone](https://dl.dropboxusercontent.com/s/6qg5x6usi6h7ews/clone.png)

La última parte de la práctica consistirá en crear un nuevo proyecto bajo licencia GNU GPL v3, que será donde subamos los archivos de nuestra aplicación.
