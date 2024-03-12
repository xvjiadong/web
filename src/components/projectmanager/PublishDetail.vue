<template>
    <div>

    </div>
</template>
<script>
import axios from 'axios'
export default {
    data() {
        return {
            version: {
                id: "",
                versionId: "",
                verName: "",
            }
        }
    },
    methods: {
        geturl(id) {
            axios.get("http://120.26.142.114:10010/dataset/url", { params: { id: id } })
                .then(res => {
                    console.log(res.data);
                }).catch(e => {
                    console.log(e);
                })
        }
    },
    mounted() {
        let query = this.$route.query
        this.version.id = query.id - 0
        this.version.name = query.name
        this.version.versionId = query.versionId - 0
        this.version.verName = query.verName
        this.geturl(this.version.id)
    },
}
</script>
<style scoped></style>
