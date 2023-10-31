<template>
    <div>
        <div @click="push('PicView')">
            图像标注
        </div>>
    </div>
</template>
<script>
export default {
    name: "MakeMark",
    components: {

    },
    data() {
        return {

        }
    },
    computed: {

    },
    methods: {
        push(item) {
            this.$router.push({
                path:`/`+item
            })
        }
    },
    mounted() {

    },
}
</script>
<style scoped></style>