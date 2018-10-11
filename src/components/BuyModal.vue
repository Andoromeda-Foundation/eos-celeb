<template>
    <form action="">
                <div class="modal-card" style="width: auto">
                    <header class="modal-card-head">
                        <p class="modal-card-title">购买 {{person.name}}</p>
                    </header>
                    <section class="modal-card-body">
                        <b-field label="Price">
                            <b-input
                                :value="price"
                                placeholder="Your Price"
                                required>
                            </b-input>
                        </b-field>
                    </section>
                    <footer class="modal-card-foot">
                        <button class="button" type="button" @click="$parent.close()">取消</button>
                        <button class="button is-primary">使用 Scatter 支付</button>
                    </footer>
                </div>
            </form>
</template>

<script>
export default {
    name: 'Buy Modal',
    props: ['person'],
    data: () => ({
        price: "0.0000 EOS"
    })
}
</script>
