<template>
  <div>
    <h2 v-if="seleccionado"> Pelicula Seleccionada: {{ seleccionado.movie }}</h2>
    <PeliculasTable :peliculas="peliculas" @nombre_pelicula="funcion_nombre" />
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue';
import PeliculasTable from '../components/Tabla_peliculas.vue'; // Importar el componente

//estado reactivo para las películas
const peliculas = ref([]);
const seleccionado = ref(null);

function funcion_nombre(payload) {
  seleccionado.value = payload;
}

onMounted(async () => {
  try {
    const response = await fetch('https://dummyapi.online/api/movies');
    const data = await response.json();
    peliculas.value = data;
  } catch (error) {
    console.error('Error fetching peliculas:', error);
  }
});
</script>
