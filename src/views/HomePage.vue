<template>
    <div class="main">
        <div class="header">
            <div class="top">
                <div class="topleft">
                    欢迎访问传统文化网！
                </div>
                <div class="topright">
                    手机版&emsp;&emsp;收藏本站
                </div>
            </div>
            <div class="headermedium">
                <img src="../../public/首页1.jpg">
                <div style="text-align: center;font-size: 30px;">
                    徐家栋<br>
                    2021339920026
                </div>
                <div>
                    <input placeholder="请输入关键词" style="height: 18px;border-radius: 5px;">
                    <input type="button" value="搜索" style="width: 70px;background-color: rgb(180,4,4);border-radius: 5px;">
                </div>
            </div>
            <div class="headerbottom">
                <ul class="direct">
                    <li v-for="(item, index) in direct" :key="index" class="directblock"><a :href="'#' + (index + 1)"
                            style="text-decoration: none;">{{ item }}</a></li>
                </ul>
            </div>
        </div>
        <div class="body" id="1">
            <div :class="{ roundimage1: pic1, roundimage2: pic2, roundimage3: pic3 }">
            </div>
            <div class="recommandlist">
                <div style="display: flex;justify-content: center;align-items: center;">
                    <div
                        style="border-radius: 5px;border: 2px solid rgb(255,111,15);color: rgb(255,111,15);width: 80px;margin-right: 15px;">
                        今日更新
                    </div>
                    <h2 style="color:black">“腊梅”“梅花”有何不同</h2><br>
                </div>
                <div style="font-size: 16px;color: rgb(140,151,74);">
                    每当梅花进入盛开期，“梅柳争春”“红梅傲雪”“悔花香自苦寒来”都会成为人们吟咏梅花的动人意象。然而，很多人不知...
                </div>
                <hr>
                <ul>
                    <li v-for="(item, index) in list" :key="index" class="listblock">
                        <div>
                            {{ item.news }}
                        </div>
                        <div>
                            {{ item.time }}
                        </div>


                    </li>
                </ul>
            </div>
        </div>
        <div style="width: 87%;margin: 0 auto;padding: 15px;background-color: ;" id="2">
            <div class="body2">
                <span style="color: rgb(180,4,4);font-weight: 600;">国学百家</span>
                <span @click="push('国学百家')">更多内容</span>
            </div>
            <hr>
            <div style="display: flex;justify-content: space-around;">
                <div>
                    <img src="../assets/1.jpeg" style="width: 500px;height: 200px;">
                    <h3 style="color: red;text-align: left;">《论语》经典名句分享</h3>
                    <div style="width: 500px;font-size: 15px;text-align: left;">
                        《论语》是最重要的儒家经典之一，是古人读书做学问的必修课程,两千年来对我们中华民族道德观念的产生和形成，起了非常重大的作用.虽然全书仅仅一万多字...
                    </div>
                    <button style="width: 500px;height: 30px;">点击产看</button>
                </div>
                <div>
                    <div v-for="(item, index) in list2" :key="index"
                        style="border: 1px solid black;padding: 5px;display: flex;align-items: center;float: left;margin-left: 15px;margin-top: 15px;">
                        <div
                            style="background-color:rgb(133,133,133);display: flex;flex-direction: column;justify-content: center;padding: 15px;">
                            <span style="color: white;font-size: 30px;">{{ item.time1 }}</span>
                            <span>{{ item.time2 }}</span>
                        </div>
                        <div
                            style="display: flex;flex-direction: column;justify-content: center;align-items: start;margin-left: 5px;width: 280px;">
                            <div style="font-size: 22px;color: black;">
                                {{ item.title }}
                            </div>
                            <div style="color:rgb(152,152,152);text-align: left;">
                                {{ item.content }}
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div style="width: 87%;margin: 0 auto;padding: 15px;background-color: ;" id="3">
            <div class="body2">
                <span style="color: rgb(180,4,4);font-weight: 600;">传统节日</span>
                <span @click="push('传统节日')">更多内容</span>
            </div>
            <hr>
            <div style="display: flex;justify-content: space-around;">
                <div>
                    <img src="../assets/春节.jpg" style="width: 500px;height: 290px;">
                    <span style="width: 500px;height: 30px;font-size: 30px;">春节</span>
                </div>
                <div>
                    <div v-for="(item, index) in list3" :key="index"
                        style="padding: 5px;float: left;margin-left: 15px;margin-top: 15px;">
                        <img :src="item.url" style="width: 230px;height: 110px;font-size: 20px;">
                        <div>{{ item.title }}</div>
                    </div>
                </div>
            </div>
        </div>
        <div style="width: 87%;margin: 0 auto;padding: 15px;background-color: ;" id="4">
            <div class="body2">
                <span style="color: rgb(180,4,4);font-weight: 600;">健康文化</span>
                <span @click="push">更多内容</span>
            </div>
            <hr>
            <div style="display: flex;justify-content: space-around;">
                <div style="display: flex;flex-direction: column;">
                    <img src="../assets/五禽戏.webp.jpg" style="width: 400px;height: 300px;">
                    <span
                        style="width: 400px;height: 30px;font-size: 30px;text-align: left;color: rgb(180,4,4);font-weight: 600;">五禽戏</span>
                    <div style="text-align: left;margin-top:5px ;width: 400px;font-size: 20px;">
                        五禽戏是中国传统导引养生的一个重要功法，其创编者华佗（约145-208），出生在东汉末沛国谯县（今安徽亳州）。其一生著述颇丰，但均亡佚。
                    </div>
                </div>
                <div>
                    <div v-for="(item, index) in list4" :key="index"
                        style="padding: 5px;float: left;margin-left: 35px;margin-top: 15px;width: 250px;">
                        <div style="display: flex;justify-content: center;align-items: start;">
                            <img :src="item.url" style="width: 240px;height: 150px;">
                            <div style="text-align: left;width: 200px;">
                                <h3>{{ item.title }}</h3>
                                <span>{{ item.content }}</span>
                            </div>
                        </div>
                    </div>
                    <div style="display: flex;justify-content: center;float: left;width: 950px;">
                        <div v-for="(item, index) in list5" :key="index"
                            style="padding: 5px;margin-left: 15px;margin-top: 15px;width: 250px;">
                            <div style="display: flex;justify-content: center;align-items: start;">
                                <img :src="item.url" style="width: 240px;height: 150px;">
                                <div style="text-align: left;width: 200px;">
                                    <h3>{{ item.title }}</h3>
                                    <span>{{ item.content }}</span>
                                </div>
                            </div>
                        </div>
                    </div>

                </div>
            </div>
        </div>
        <div style="width: 87%;margin: 0 auto;padding: 15px;background-color: ;" id="5">
            <div class="body2">
                <span style="color: rgb(180,4,4);font-weight: 600;">人文地理</span>
                <span @click="push('人文地理')">更多内容</span>
            </div>
            <hr>
            <div style="display: flex;justify-content: space-around;">
                <div>
                    <img src="../assets/1 (1).jpeg" style="width: 500px;height: 290px;">
                    <span style="width: 500px;height: 30px;font-size: 30px;">北京</span>
                </div>
                <div>
                    <div v-for="(item, index) in list6" :key="index"
                        style="padding: 5px;float: left;margin-left: 15px;margin-top: 15px;">
                        <img :src="item.url" style="width: 230px;height: 110px;font-size: 20px;">
                        <div>{{ item.title }}</div>
                    </div>
                </div>
            </div>
        </div>
        <div style="width: 87%;margin: 0 auto;padding: 15px;background-color: ;" id="6">
            <div class="body2">
                <span style="color: rgb(180,4,4);font-weight: 600;">文学艺术</span>
                <span @click="push('文学艺术')">更多内容</span>
            </div>
            <hr>
            <div style="display: flex;justify-content: space-around;">
                <div>
                    <img src="../assets/总.jpg" style="width: 500px;height: 290px;">
                    <span style="width: 500px;height: 30px;font-size: 30px;">儒</span>
                </div>
                <div>
                    <div v-for="(item, index) in list7" :key="index"
                        style="padding: 5px;float: left;margin-left: 15px;margin-top: 15px;">
                        <img :src="item.url" style="width: 230px;height: 110px;font-size: 20px;">
                        <div>{{ item.title }}</div>
                    </div>
                </div>
            </div>
        </div>
        <div style="width: 87%;margin: 0 auto;padding: 15px;background-color: ;" id="7">
            <div class="body2">
                <span style="color: rgb(180,4,4);font-weight: 600;">华夏历史</span>
                <span @click="push('华夏历史')">更多内容</span>
            </div>
            <hr>
            <div style="display: flex;justify-content: space-around;">
                <div>
                    <img src="../assets/中国.webp.jpg" style="width: 500px;height: 290px;">
                    <span style="width: 500px;height: 30px;font-size: 30px;">中华</span>
                </div>
                <div>
                    <div v-for="(item, index) in list8" :key="index"
                        style="padding: 5px;float: left;margin-left: 15px;margin-top: 15px;">
                        <img :src="item.url" style="width: 230px;height: 110px;font-size: 20px;">
                        <div>{{ item.title }}</div>
                    </div>
                </div>
            </div>
        </div>
        <div style="height: 90px;"></div>
        <div class="footer">
            <div style="letter-spacing: 8px;white-space: pre-wrap;color: white;">
                国学百家 | 传统节日 | 健康文化 | 人文地理 | 文学艺术 | 华夏历史
            </div>
            <div style="text-align: center;color: white;">
                Copyright@2020-2023传统文化网版权所有<br>
                声明:本网站部分文章和图片系转载。如侵犯了您的权利和版权.请告知我们予以删除。
            </div>
        </div>
    </div>
</template>
<script>
export default {
    methods: {
        push(item) {
            this.$router.push({
                path: '/son',
                query: {
                    num: { ID: this.direct.indexOf(item) - 1 }
                }
            })
        }
    },
    data() {
        return {
            direct: ["首页", "国学百家", "传统节日", "健康文化", "人文地理", "文学艺术", "华夏历史"],
            pic1: true,
            pic2: false,
            pic3: false,
            round: "",
            picnum: 1,
            list: [
                { news: "中国端午文化的发源与继承", time: "06-10" },
                { news: "中药店称为“堂”的典故", time: "05-16" },
                { news: "墨家的“节用”思想与人性需要之间的矛盾", time: "05-10" },
                { news: "中国古代文化常识之服饰代称", time: "05-05" },
                { news: "《诗经·关雎》中的“河之洲”到底在哪?", time: "04-11" },
                { news: "寒食已随云影杳祭祖无妨踏青游", time: "04-03" },
                { news: "药补不及食补︰食补不及动补", time: "03-30" }
            ],
            list2: [
                {
                    time1: "20",
                    time2: "2021-04",
                    title: "国学常识之科举制度",
                    content: "科举制度是中国封建社会通过考试选拔官员的—种基本制度,创始于隋朝确立于唐朝完备..."
                },
                {
                    time1: "12",
                    time2: "2021-04",
                    title: "儒家何以被称为“百家之首”",
                    content: "在春秋战国时期，曾经出现过林林总总的不同学术流派，被称为'诸子百家'。其实。所调."
                },
                {
                    time1: "30",
                    time2: "2021-03",
                    title: "书法，让人走向至高境界",
                    content: "习练书法时，要严格遵循书写资势和执笔要求，姿势不正，执笔无法，就不能挥笔运睪..."
                },
                {
                    time1: "20",
                    time2: "2021-03",
                    title: "认识《黄帝内经》",
                    content: "《黄帝内经》分《灵枢》、《素问》两部分，是中国最早的医学典籍，传统医学四大经典"
                },
                {
                    time1: "04",
                    time2: "2021-03",
                    title: "我国古代的“成人”礼仪",
                    content: "我国古代非常重视“成人”礼仪,注重发挥其在人们世界观、人生观、价值观形成中的教."
                },
                {
                    time1: "05",
                    time2: "2021-01",
                    title: "从汉亨演变看“福””祸”之混",
                    content: "春节即至，大家互相祝贺，形成了新年气氛。中国人传统做法写春联.送福字。但谁也没..."
                }
            ],
            list3: [
                {
                    url: require("../assets/元宵节.jpg"),
                    title: "元宵节"
                },
                {
                    url: require("../assets/清明节.jpg"),
                    title: "清明节"
                },
                {
                    url: require("../assets/端午.jpg"),
                    title: "端午节"
                },
                {
                    url: require("../assets/中秋.jpg"),
                    title: "中秋节"
                },
                {
                    url: require("../assets/重阳节.jpg"),
                    title: "重阳节"
                },
                {
                    url: require("../assets/腊八节.jpg"),
                    title: "腊八节"
                },
            ],
            list4: [
                {
                    url: require("../assets/鹿戏.jpg"),
                    title: "鹿戏",
                    content: "四肢距地，前三掷，却二掷，长引腰，侧脚仰天，即返距行，前、却各七过也。"
                },
                {
                    url: require("../assets/虎戏.jpg"),
                    title: "虎戏",
                    content: "四肢距地，引项反顾，左三右二，左右伸脚，伸缩亦三亦二也。"
                },
                {
                    url: require("../assets/熊戏.jpg"),
                    title: "熊戏",
                    content: "正仰以两手抱膝下，举头，左擗地七，右亦七，蹲地，以手左右托地。"
                },
            ],
            list5: [
                {
                    url: require("../assets/猿戏.jpg"),
                    title: "猿戏",
                    content: "攀物自悬，伸缩身体，上下一七，以脚拘物自悬，左右七，手钩却立，按头各七。"
                },
                {
                    url: require("../assets/飞鸟戏.jpg"),
                    title: "鸟戏",
                    content: "双立手，翘一足，伸两臂，扬眉鼓力，各二七，坐伸脚，手挽足距各七，缩伸二臂各七也。"
                }
            ],
            list6: [
                {
                    url: require("../assets/2.jpeg"),
                    title: "浙江"
                },
                {
                    url: require("../assets/3.jpeg"),
                    title: "辽宁"
                },
                {
                    url: require("../assets/4.jpeg"),
                    title: "广东"
                },
                {
                    url: require("../assets/5.jpeg"),
                    title: "西藏"
                },
                {
                    url: require("../assets/6.jpeg"),
                    title: "内蒙古",
                },
                {
                    url: require("../assets/7.jpeg"),
                    title: "湖北",
                }
            ],
            list7: [
                {
                    url: require("../assets/2.webp.jpg"),
                    title: "诗"
                },
                {
                    url: require("../assets/3.jpeg"),
                    title: "书"
                },
                {
                    url: require("../assets/礼.webp.jpg"),
                    title: "礼"
                },
                {
                    url: require("../assets/乐.webp.jpg"),
                    title: "乐"
                },
                {
                    url: require("../assets/易.jpeg"),
                    title: "易",
                },
                {
                    url: require("../assets/春秋.webp.jpg"),
                    title: "春秋",
                }
            ],
            list8: [
                {
                    url: require("../assets/汉.jpeg"),
                    title: "汉"
                },
                {
                    url: require("../assets/唐.jpg"),
                    title: "唐"
                },
                {
                    url: require("../assets/宋.jpeg"),
                    title: "宋"
                },
                {
                    url: require("../assets/元.jpeg"),
                    title: "元"
                },
                {
                    url: require("../assets/明.webp.jpg"),
                    title: "明",
                },
                {
                    url: require("../assets/清.png"),
                    title: "清",
                }
            ],
        }
    },
    mounted() {
        this.round = setInterval(() => {
            this.pic1 = false
            this.pic2 = false
            this.pic3 = false
            if (this.picnum % 3 == 1) {
                this.pic1 = true
            } else if (this.picnum % 3 == 2) {
                this.pic2 = true
            } else if (this.picnum % 3 == 0) {
                this.pic3 = true
            }
            this.picnum += 1
        }, 3000)
    }
}
</script>
<style scoped>
.body2 {
    display: flex;
    padding: 3px;
    margin: 0 auto;
    justify-content: space-between;
}

.body {
    display: flex;
    padding: 15px;
    justify-content: space-around;
}

.roundimage1 {
    width: 600px;
    height: 300px;
    background-size: 100% 100%;
    background-repeat: no-repeat;
    background-image: url('../assets/1.jpeg');
}

.roundimage2 {
    width: 600px;
    height: 300px;
    background-size: 100% 100%;
    background-repeat: no-repeat;
    background-image: url('../assets/绿茶1.jpg');
}

.roundimage3 {
    width: 600px;
    height: 300px;
    background-size: 100% 100%;
    background-repeat: no-repeat;
    background-image: url('../assets/红茶3.jpg');
}

.recommandlist {
    width: 600px;
    height: 300px;
}

.main {
    height: 100%;
    width: 100%;
}

.footer {
    position: fixed;
    bottom: 0;
    height: 10%;
    width: 100%;
    background-color: rgb(51, 51, 51);
    display: flex;
    flex-direction: column;
    justify-content: space-around;
    align-items: center;
    padding: 10px;
}

.top {
    background-color: rgb(243, 243, 243);
    display: flex;
    height: 5%;
    padding-left: 5px;
    padding-right: 30px;
    justify-content: space-between;
}

.headermedium {
    display: flex;
    height: 2%;
    padding-left: 5px;
    padding-right: 30px;
    justify-content: space-between;
    align-items: center;
}

.headerbottom {
    height: 5%;
}

.direct {
    background-color: rgb(180, 4, 4);
    display: flex;
    justify-content: space-around;
    list-style: none;
}

.directblock {
    padding: 10px;
    font-size: 25px;
    cursor: pointer;
    color: rgb(249, 245, 250);
}

.directblock:hover {
    padding: 15px;
    font-size: 30px;
    color: black;
}

.listblock {
    display: flex;
    justify-content: space-between;
    cursor: pointer;
}

.listblock:hover {
    color: blueviolet;
    text-decoration: underline;
}
</style>