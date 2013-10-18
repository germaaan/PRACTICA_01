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

	<p> <h1> Datos del alumno </h1> </p>

	<?php

		ini_set('display_errors', true);
		error_reporting(E_ALL);

		require_once "Alumno.class.inc";

		if(isset($_GET["campoIdAlumno"])){
			$idAlumno = $_GET["campoIdAlumno"];

			if(Alumno::existeAlumno($idAlumno)){
				Alumno::mostrarDatosAlumno(Alumno::getDatosAlumno($idAlumno));
			} else {
				echo "<p> No existe ningun alumno con el identificador \"".$idAlumno."\".</p>";
			}
		} else {
			echo "<p><h3> Error al recibir los datos del formulario. Por favor, retroceda y vuelva a rellenarlo. </h2><p>";
		}

  ?>
    
  <h2>
    Enlaces:
  </h2>
  <ul>
    <li>
      Pagina de <a href="http://acceso-germaaan.rhcloud.com/" > inicio </a>.
    </li>
    <li>
      Repositorio <a href="https://github.com/IV-GII/GII-2013"> GII-2013 </a> con el material de la asignatura.
    </li>
    <li>
      Repositorio <a href="https://github.com/germaaan/PRACTICA_01" > PRACTICA_01 </a> con el código de la aplicación.
    </li>
    <li>
     <a href="https://twitter.com/iv_gii"> Twitter </a> de la asignatura.
    </li>
  </ul>
</body>
</html>

