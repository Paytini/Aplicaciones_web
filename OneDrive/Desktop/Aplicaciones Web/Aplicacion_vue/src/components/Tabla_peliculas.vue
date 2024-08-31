<!-- Aqui seria mi componente para solo usarlo en algun otro vista de la pagina -->

<template>
    <div>
      <h1>Películas</h1>
      <table>
        <thead>
          <tr>
            <th>Título</th>
            <th>Calificación</th>
            <th>IMDB</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="pelicula in peliculas" :key="pelicula.id">
            <td>{{ pelicula.movie }}</td>
            <td>{{ pelicula.rating }}</td>
            <td><a :href="pelicula.imdb_url" target="_blank">{{ pelicula.imdb_url }}</a></td>
          </tr>
        </tbody>
      </table>
    </div>
  </template>
  
  <script>
  export default {
    name: 'Tabla_peliculas',
    props: {
      peliculas: {
        type: Array, // lo ocupa
        required: true
      }
    }
  };
  </script>
  
  <style scoped>
  table {
    width: 100%;
    border-collapse: collapse;
  }
  
  th, td {
    padding: 10px;
    border: 1px solid #ddd;
    text-align: left;
  }
  
  th {
    background-color: #f2f2f2;
    font-weight: bold;
  }
  
  a {
    color: green;
    text-decoration: none;
  }
  
  h1 {
    text-align: center;
  }
  </style>
  