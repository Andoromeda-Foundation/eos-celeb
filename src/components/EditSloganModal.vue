<template>
  <form action="">
    <div class="modal-card" style="min-width: 500px; width: auto">
      <header class="modal-card-head">
        <p class="modal-card-title">修改标语</p>
      </header>
      <section class="modal-card-body">
        <b-field label="标语内容 (最长 64 字符)">
          <b-input maxlength="64" type="textarea" v-model="slogan"></b-input>
        </b-field>
      </section>
      <footer class="modal-card-foot">
        <button class="button is-rounded is-primary" @click="edit()">保存修改</button>
        <button class="button is-rounded" @click="$parent.close()">关闭</button>
      </footer>
    </div>
  </form>
</template>

<script>
import { mapState, mapGetters } from 'vuex'

export default {
  name: 'EditSloganModal',
  props: ['priceInfo'],
  data: () => ({
    slogan: '',
  }),
  mounted: function () {
    // Initialize default value
    this.slogan = this.priceInfo.slogan
  },
  methods: {
    edit() {
      console.log(this.slogan)
    }
  },
  computed: {
    ...mapState(['identity', 'scatter', 'eos', 'account']),
    ...mapGetters(['account'])
  }
}
</script>
