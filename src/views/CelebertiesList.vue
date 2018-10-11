<template>
    <div class="celeb-list">
        <!-- {{celebs}} -->
        <div class="columns is-multiline">
            <div class="column is-3" v-for="celeb in celebs" :key="celeb.id">
                <div class="card">
                    <div class="card-image">
                        <figure class="image is-4by4">
                            <img :src="`https://eosheros.togetthere.cn/image/${celeb.id}.jpg`" class="is-rounded celeb-avatar" alt="Placeholder image">
                        </figure>
                    </div>
                    <div class="card-content">
                        <div class="media">
                        <!-- <div class="media-left">
                            <figure class="image is-48x48">
                            <img src="https://bulma.io/images/placeholders/96x96.png" alt="Placeholder image">
                            </figure>
                        </div> -->
                        <div class="media-content">
                            <p class="title is-4">{{celeb.name}}</p>
                            <p class="subtitle is-6"> {{celeb.price}} </p>
                        </div>
                        </div>

                        <div class="content">
                        主人留言: 我是菜鸡.
                        <a href="#">#css</a> <a href="#">#responsive</a>
                        <br>
                        <button class="button is-large"> 以 {{celeb.price}} 购买 </button>
                        </div>
                    </div>
                    </div>
            </div>
        </div>
    </div>
</template>

<script>
import { getCelebs } from "../blockchain/celeb";
export default {
  name: "celeberties-list",
  data: () => ({
    celebs: []
  }),
  async created() {
      this.celebs = await getCelebs()
  },
  methods: {}
};
</script>

<style scoped>
.card {
    text-align: center
}
.media-content * {
     text-align: center
}
</style>
