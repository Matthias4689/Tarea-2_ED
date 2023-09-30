# Tarea 2
# Gestor de Información Turística

## Descripción
Esta tarea consiste en la creación de una aplicación de gestión de información turística. La aplicación permitirá a los usuarios llevar un registro de puntos de interés turístico, turistas y sus listas de lugares favoritos. Los usuarios podrán realizar diversas acciones, como registrar nuevos puntos de interés, mostrar información detallada de los lugares, eliminar puntos de interés, registrar turistas, agregar lugares favoritos a los turistas, visualizar turistas por país y filtrar puntos de interés por tipo. Además, implementa la capacidad de importar datos desde archivos CSV y exportar información a archivos CSV para facilitar la administración de datos. 


## Cómo compilar y ejecutar

1. Clonar el repositorio:
    
    ```
    https://github.com/Matthias4689/Tarea-2_ED.git
    
    ```
    
2. Navegar al directorio del proyecto:
    
    ```
    cd Tarea-2_ED
    
    ```
    
3. Compilar el código:
    
    ```
    gcc main.c funciones.h list.h hashmap.h funciones.c list.c hashmap.c puntos_interes.csv turistas.csv puntosDeInteresExportar.csv turistasExportar.csv -o gestor
    
    ```
    
4. Ejecutar la aplicación:
    
    ```
    ./gestor
    
    ```
    

## Funcionalidades

### Funcionando correctamente:

- Registrar punto de interés.
- Mostrar datos de punto de interés.
- Eliminar punto de interés.
- Registrar turista.
- Agregar lugar favorito a turista.
- Mostrar turistas por país.
- Mostrar todos los puntos de interés de un tipo.
- Importar puntos de interés y turistas desde archivos CSV.
- Exportar puntos de interés y turistas a archivos CSV

### Problemas conocidos:

- Algunas operaciones pueden tener problemas si se ingresan datos incorrectos o si se intenta realizar una acción inválida. Se recomienda seguir las instrucciones y restricciones proporcionadas en las funciones para evitar problemas. Aún estamos investigando algunas posibles soluciones.
- ....................

### A mejorar:

- Ordenar automáticamente la lista de lugares turísticos por nombre o tipo.
- Permitir la edición de información de lugares turísticos existentes.
- Agregar la opcion de comentarios y calificaciones de los lugares de interés, para crear una lista con los 10 mejores de mayor a menor.

## Contribuciones
 [Puntaje asignado entre 0 y 3] (0=Aporte insuficiente, 1=Aporte satisfactorio, 2=Aporte bueno, 3=Aporte excelente).

### Javier Donetch:

- Desarrolló las funciones ....
- Diseño inicial de la interfaz de usuario.
- **Auto-evaluación**: 

### Matias Romero:

- Implementó la función de eliminar tareas.
- Documentación y comentarios en el código.
- Diseño y redacción del README.
- **Auto-evaluación**: 
