<template>
    <div></div>
</template>
<script>
import axios from 'axios'
export default {
    data() {
        return {
            t: 0,
            s: 0
        }
    },
    methods: {
        post() {
            axios.post("http://localhost:5000/api/segment_manual", {
                "box": [106.25, 80.05555555555556, 335.4166666666667, 329.36111111111114, "1710485199807"],
                "point": [],
                "url": "https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-02-29/469b8cdaf9f74bb4ada074c77d4ed242-目标分割2/V1/objects365_v1_00147159.jpg"
            }).then(res => {
                this.t += res.data.t
                this.s += 1
                if (this.s !== 50) {
                    console.log(res.data.t);
                } else {
                    console.log(this.t);
                }
            })
        }
    },
    mounted() {
        /*let a = setInterval(() => {
            if (this.s == 50) {
                a.clearInterval()
                console.log(this.t);
            }
            this.post()
        }, 5000)*/

    }
}
</script>