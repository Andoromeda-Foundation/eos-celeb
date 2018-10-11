<template>
  <div class="home">
    <Celeb></Celeb>
  </div>
</template>

<script>
// @ is an alias to /src
import Celeb from './CelebertiesList.vue'

export default {
  name: 'home',
  components: {
    Celeb
  }
}
</script>
