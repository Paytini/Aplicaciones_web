<template>
    <div>
      <PeliculasTable :peliculas="peliculas" />
    </div>
  </template>
  
  <script>
  import { onMounted, ref } from 'vue';
  import PeliculasTable from '../components/Tabla_peliculas.vue'; // Importar el componente
  
  export default {
    name: 'Peliculas',
    components: {
      PeliculasTable
    },
    setup() {
      const peliculas = ref([]);
  
      onMounted(async () => {
        try {
          const response = await fetch('https://dummyapi.online/api/movies');
          const data = await response.json();
          peliculas.value = data;
        } catch (error) {
          console.error('Error fetching peliculas:', error);
        }
      });
  
      return { peliculas };
    }
  };
  </script>
  