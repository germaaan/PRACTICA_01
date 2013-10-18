<?php 

	ini_set('display_errors', true);
	error_reporting(E_ALL);
	
	require_once "/var/lib/openshift/525c7ef35004461e1f00009d/mysql/configuracion.inc";
	
	class Alumno{

		public static function conectar(){
			try {
				$codif = array(PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8',); 
				$conexion = new PDO( DB_DSN, DB_USUARIO, DB_PASS, $codif);
				$conexion->setAttribute( PDO::ATTR_PERSISTENT, TRUE );
				$conexion->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
			}
			catch ( PDOException $e) {
				exit( 'Conexión fallida: '. $e->getMessage() );
			}
 
			return $conexion;
		}
 
		public static function desconectar( $conexion ){
			$conexion = NULL;
		}

		public static function getListadoAlumnos(){
                        $conexion = Alumno::conectar();

                        $sql = "SELECT * FROM ".TABLA_ALUMNOS;

                        try{
                            	$st = $conexion->prepare($sql);
                                $st->execute();
				$alumnos = array();

                                foreach($st->fetchAll() as $fila){
					$alumnos[] = $fila["id_alumno"];
				}

                                Alumno::desconectar($conexion);

                                return $alumnos;
                        }catch(PDOException $e){
                                Alumno::desconectar($conexion);
                                die("Consulta fallida: ".$e->getMessage());
                        }
                }

		public static function mostrarListado($datos){
			echo "<ul style='list-style-type:circle'>";

			foreach($datos as $alumno){
				echo "<li> <a href='http://acceso-germaaan.rhcloud.com/acceso.php?campoIdAlumno=".$alumno."'> ".$alumno." </a> </li>";
			}

			echo "</ul>";
		}

		public static function existeAlumno($id_alumno){
			$conexion = Alumno::conectar();
			
			$sql = "SELECT * FROM ".TABLA_ALUMNOS." WHERE id_alumno = :id_alumno";
			
			try{
				$st = $conexion->prepare($sql);
				$st->bindValue(":id_alumno",$id_alumno,PDO::PARAM_STR);
				$st->execute();

				$result = $st->fetch();
				
				Alumno::desconectar($conexion);
				
				if($result)
					return true;
			}catch(PDOException $e){
				Alumno::desconectar($conexion);
				die("Consulta fallida: ".$e->getMessage());
			}
		}

		public static function getDatosAlumno($id_alumno){
			$conexion = Alumno::conectar();
			
			$sql = "SELECT * FROM ".TABLA_ALUMNOS." WHERE id_alumno = :id_alumno";
			
			try{
				$st = $conexion->prepare($sql);
				$st->bindValue(":id_alumno",$id_alumno,PDO::PARAM_STR);
				$st->execute();

				$result = $st->fetch();
				
				Alumno::desconectar($conexion);
				
				if($result)
					return $result;
				else
					return NULL;
			}catch(PDOException $e){
				Alumno::desconectar($conexion);
				die("Consulta fallida: ".$e->getMessage());
			}
		}
		
		public static function mostrarDatosAlumno($datos){
			echo "<ul style='list-style-type:circle'>";
			
			echo "<li> <br>Alumno: <a href='https://github.com/".$datos["id_alumno"]."'>".$datos["id_alumno"]."</a>".
				"<br>Nombre: ".$datos["nombre"].
				"<br>Apellidos: ".$datos["apellidos"].
				"<br>Direccion correo: <a href='mailto:".$datos["correo"]."'>".$datos["correo"]."</a>".
				"<br>Twitter: <a href='https://twitter.com/".$datos["twitter"]."'>".$datos["twitter"]."</a>".
				"</li>";
			
			echo "</ul>";
		}

	}
?>

