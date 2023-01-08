Trabajo Realizado por Andrés López Torres
Diciembre 2022 

Se revisaron los enlaces propuestos de los retos de Raylib, posteriormente se realizó la implementación utilizando C++ (Programación Orientada a Objetos)
Se realizó lo más cercano al juego solicitado en la guía PDF, mantiniendo algo de estructura, pero buscando funcionalidad por encima de todo..
Lastimosamente no pude refinar todo el código, ya que en un principio lo hice en Lenguaje C y para darle una estructura aún me cuesta algo de trabajo
Enumero los puntos realizados:
•	Se crea el escenario con tilemaps, por medio de archivos txt.
•	Se organiza el motodo de carga de tilemaps, para recibir los 3 parametros de texto
•	Se implementaron las animaciones de pacman, al cambiar de direccion y al morir.
•	En el juego original despues de un rato empieza solo, pero lo implemente de acuerdo a las respuesta en los foros, se debe presionar A o D respectivamente para empezar a jugar.
•	Se contabiliza el puntaje de acuerdo con lo solicitado, 10 por cada punto, 50 por cada power pill y 200 si logramos comer el fantasma
•	El fantasma se añade con animaciones y direcciones, ademas de los estados, necesarios (CHASE, FRIGHTENED, EATEN y adicionalmente INHOME para que pueda salir de la casa solo al estar en ese estado).
•	El fantasma cada que llega a un nuevo tile, calcula la dirección que debe tomar de acuerdo a lo expuesto en la guía.
•	Se incorpora una música y efectos de sonido que se dieron como recursos
•	Se muestra el numero de vidas de pacman y al perder se reinicia el juego por completo.
•	Si solo perdemos una vida, continuamos desde donde quedamos.
•	Se indica al jugador si gana o pierde.
•	Se realizaron las siguientes pantallas:
	•	Pantalla de Logo
	•	Pantalla de Titulo
	•	Pantalla de Opciones
	•	Pantalla de Juego
	•	Pantalla de fin de juego

Se buscó coherencia y dejar la estructura de objetos siempre pensando en el Game Loop, Init, Update, Drawing y Finalización.
Como suele pasarme, trato de hacer lo mejor que puedo en el game feeling y no pude entregar el trabajo con todos los refinamientos que quería, pero como es de costumbre disfruto mucho programar videojuegos, 
ademas del aprendizaje obtenido. Espero tener la oportunidad de seguir aprendiendo y reforzar mis conocimientos en programación, ¡ojalá disfrute el trabajo y nos vemos en el Aula :)!
