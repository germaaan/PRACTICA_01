<!doctype html>
<html lang="es">
<head>
  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
  <link rel="stylesheet" href="index.css">
  <title>Plataforma Acceso</title>
</head>
<body>
  <h1>
    Bienvenido a Infraestructura Virtual!
  </h1>

  <p><h1>Formulario de acceso</h1></p>
  <form action="acceso.php" method=get>
    <fieldset>
      <label for="campoIdAlumno"> Id. Alumno: </label>
      <input type="text" name="campoIdAlumno" maxlength="20"/>
      <br/><br/>

      <input type="reset" name="botonReiniciar" value="Borrar datos"/>
      <input type="submit" name="botonEnviar" value="Enviar datos"/>
      <a href="http://acceso-germaaan.rhcloud.com/listado.php"> Listado de identificadores </a>
    </fieldset>
  </form>
    
  <h2>
    Enlaces:
  </h2>
  <ul>
    <li>
      Repositorio <a href="https://github.com/IV-GII/GII-2013"> GII-2013 </a> con el material de la asignatura.
    </li>
    <li>
      Repositorio <a href="https://github.com/germaaan/PRACTICA_01" > PRACTICA_01 </a> con el código de la aplicación.
    </li>
    <li>
      <a href="https://twitter.com/iv_gii"> Twitter </a>  de la asignatura.
    </li>
    <li>
      Toda la aplicacion publicada bajo licencia GNU GENERAL PUBLIC LICENSE Version 3. 
    </li>
  </ul>
</body>
</html>

