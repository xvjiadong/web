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
                    <li v-for="(item, index) in direct" :key="index" class="directblock" @click="ch(index)"><a
                            :href="'#' + (index + 1)" style="text-decoration: none;">{{ item }}</a></li>
                </ul>
            </div>
        </div>
        <div class="body">
            <div style="width: 72%;">
                <div style="width: 98%;text-align: left;background-color: white;padding-left: 15px;">
                    <h2 style="color: rgb(180,4,4);margin: 0px;">{{ choose[chindex].title}}</h2>
                    <span style="color: rgb(132,132,132);">
                        {{ choose[chindex].descript }}
                    </span>
                </div>
                <div style="width:100%;margin-top: 15px;">
                    <div
                        style="width: 100%;display: flex;justify-content: space-between;padding: 10px;align-items: center;">
                        <span style="color:rgb(180,4,4);font-weight: 600;font-size: 20px;">{{ choose[chindex].title}}</span>
                        <span style="margin-right: 3%;">当前位置:首页->{{ choose[chindex].title }}</span>
                    </div>
                    <hr style="margin-top: 0;width: 97%;">
                </div>
                <div style="width:100%;margin-top: 10px;background-color: white;">
                    <ul style="padding: 25px;list-style: square;">
                        <li v-for="(item, index) in choose[chindex].list.slice((currentPage - 1) * pageSize, currentPage * pageSize)"
                            :key="index" style="margin-top: 5px;cursor: pointer;"
                            @click="push">
                            <div style="display: flex;justify-content: space-between;">
                                <span>{{ item.listtitle }}</span>
                                <span>{{ item.time }}</span>
                            </div>
                            <hr style="border: 1px dotted rgb(132,132,132);margin: 0;">
                        </li>
                    </ul>
                </div>
                <el-pagination :current-page="currentPage" :page-sizes="[5, 10, 15, 20]" :page-size="pageSize" background
                    layout="sizes, prev, pager, next, jumper" :total="choose[chindex].list.length"
                    @size-change="handleSizeChange" @current-change="handleCurrentChange" />
            </div>
            <div style="width: 28%;height: 40%;background-color: white;">
                <div style="padding: 5px;text-align: left;">
                    <h3 style="margin: 0;font-size: 25px;padding-left: 7px;">推荐文章</h3>
                    <hr style="border: 1px dotted rgb(132,132,132);margin: 0;">
                    <ul style="padding-left: 25px;list-style: square;margin: 0;">
                        <li v-for="(item, index) in choose[chindex].recommand" :key="index"
                            style="margin-top: 5px;cursor: pointer;"
                            @click="push">
                            <div style="display: flex;justify-content: start;">
                                <span>{{ item.listtitle }}</span>
                            </div>
                            <hr style="border: 1px dotted rgb(132,132,132);margin: 5px;">
                        </li>
                    </ul>
                </div>
                <div style="padding: 5px;text-align: left;height: 40%;">
                    <h3 style="margin: 0;font-size: 25px;padding-left: 7px;">热点文章</h3>
                    <hr style="border: 1px dotted rgb(132,132,132);margin: 0;">
                    <ul style="padding-left: 25px;list-style: square;margin: 0;">
                        <li v-for="(item, index) in choose[chindex].hot" :key="index" style="margin-top: 5px;" @click="push">
                            <div style="display: flex;justify-content: start;cursor: pointer;">
                                <span>{{ item.listtitle }}</span>
                            </div>
                            <hr style="border: 1px dotted rgb(132,132,132);margin: 5px;">
                        </li>
                    </ul>
                </div>
            </div>
        </div>
    </div>
</template>
<script>
export default {
    mounted() {
        this.chindex=this.$route.query.num.ID
    },
    methods: {
        push() {
            this.$router.push("/detail")  
        },
        handleSizeChange(val) {
            this.pageSize = val
        },
        handleCurrentChange(val) {
            this.currentPage = val
        },
        ch(index) {
            this.chindex = index
            this.pageSize = 20
            this.currentPage = 1
        }
    },
    data() {
        return {
            chindex: 0,
            currentPage: 1,
            pageSize: 20,
            direct: ["国学百家", "传统节日", "健康文化", "人文地理", "文学艺术", "华夏历史"],
            choose: [
                {
                    title: "国学百家",
                    descript: "国学，是以先秦经典及诸子百家学说为根基，它涵盖了两汉经学、魏晋充学、隋唐道学、宋明理学、明清实学和同时期的先秦诗赋、汉赋、六潮骈文、唐宋诗词....",
                    list: [
                        {
                            listtitle: "中国端午文化的发源与继承",
                            time: "06-10"
                        },
                        {
                            listtitle: "中药店称为“堂”的典故",
                            time: "05-16"
                        },
                        {
                            listtitle: "墨家的“节用”思想与人性需要之间的矛盾",
                            time: "05-10"
                        },
                        {
                            listtitle: "中国古代文化常识之服饰代称",
                            time: "05-05"
                        },
                        {
                            listtitle: "中国端午文化的发源与继承",
                            time: "04-11"
                        },
                        {
                            listtitle: "《诗经·关雎》中的“河之洲”到底在哪?",
                            time: "04-03"
                        },
                        {
                            listtitle: "寒食已随云影查祭祖无妨踏青游",
                            time: "03-30"
                        },
                        {
                            listtitle: "国学常识之科举制度",
                            time: "03-30"
                        },
                        {
                            listtitle: "儒家何以被称为“百家之首”",
                            time: "03-30"
                        },
                        {
                            listtitle: "书法，让人走向至高境界",
                            time: "03-30"
                        },
                        {
                            listtitle: "认识《黄帝内经》",
                            time: "03-30"
                        },
                        {
                            listtitle: "我国古代的“成人”礼仪",
                            time: "03-30"
                        },
                        {
                            listtitle: "从汉字演变看“福””祸”之混",
                            time: "03-30"
                        },
                        {
                            listtitle: "范仲淹:处事莫如为善，传家唯有读书",
                            time: "03-30"
                        },
                        {
                            listtitle: "什么是“八拜之交”、“生死之交”?",
                            time: "03-30"
                        },
                        {
                            listtitle: "动物成语中“昆虫成语”最多",
                            time: "03-30"
                        },
                        {
                            listtitle: "[周易]周易第一卦:乾卦乾为天乾上乾下",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语名句]子夏曰;“博学而笃志，切问而近思，仁在其中矣。”",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语]论语全文带拼音完整版",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语名句]子曰:“吾尝终日不食，终夜不寝，以思，无益，不如学也。”",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语]学而第一",
                            time: "03-10"
                        },
                        {
                            listtitle: "中国端午文化的发源与继承",
                            time: "06-10"
                        },
                        {
                            listtitle: "中药店称为“堂”的典故",
                            time: "05-16"
                        },
                        {
                            listtitle: "墨家的“节用”思想与人性需要之间的矛盾",
                            time: "05-10"
                        },
                        {
                            listtitle: "中国古代文化常识之服饰代称",
                            time: "05-05"
                        },
                        {
                            listtitle: "中国端午文化的发源与继承",
                            time: "04-11"
                        },
                        {
                            listtitle: "《诗经·关雎》中的“河之洲”到底在哪?",
                            time: "04-03"
                        },
                        {
                            listtitle: "寒食已随云影查祭祖无妨踏青游",
                            time: "03-30"
                        },
                        {
                            listtitle: "国学常识之科举制度",
                            time: "03-30"
                        },
                        {
                            listtitle: "儒家何以被称为“百家之首”",
                            time: "03-30"
                        },
                        {
                            listtitle: "书法，让人走向至高境界",
                            time: "03-30"
                        },
                        {
                            listtitle: "认识《黄帝内经》",
                            time: "03-30"
                        },
                        {
                            listtitle: "我国古代的“成人”礼仪",
                            time: "03-30"
                        },
                        {
                            listtitle: "从汉字演变看“福””祸”之混",
                            time: "03-30"
                        },
                        {
                            listtitle: "范仲淹:处事莫如为善，传家唯有读书",
                            time: "03-30"
                        },
                        {
                            listtitle: "什么是“八拜之交”、“生死之交”?",
                            time: "03-30"
                        },
                        {
                            listtitle: "动物成语中“昆虫成语”最多",
                            time: "03-30"
                        },
                        {
                            listtitle: "[周易]周易第一卦:乾卦乾为天乾上乾下",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语名句]子夏曰;“博学而笃志，切问而近思，仁在其中矣。”",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语]论语全文带拼音完整版",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语名句]子曰:“吾尝终日不食，终夜不寝，以思，无益，不如学也。”",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语]学而第一",
                            time: "03-10"
                        },
                        {
                            listtitle: "中国端午文化的发源与继承",
                            time: "06-10"
                        },
                        {
                            listtitle: "中药店称为“堂”的典故",
                            time: "05-16"
                        },
                        {
                            listtitle: "墨家的“节用”思想与人性需要之间的矛盾",
                            time: "05-10"
                        },
                        {
                            listtitle: "中国古代文化常识之服饰代称",
                            time: "05-05"
                        },
                        {
                            listtitle: "中国端午文化的发源与继承",
                            time: "04-11"
                        },
                        {
                            listtitle: "《诗经·关雎》中的“河之洲”到底在哪?",
                            time: "04-03"
                        },
                        {
                            listtitle: "寒食已随云影查祭祖无妨踏青游",
                            time: "03-30"
                        },
                        {
                            listtitle: "国学常识之科举制度",
                            time: "03-30"
                        },
                        {
                            listtitle: "儒家何以被称为“百家之首”",
                            time: "03-30"
                        },
                        {
                            listtitle: "书法，让人走向至高境界",
                            time: "03-30"
                        },
                        {
                            listtitle: "认识《黄帝内经》",
                            time: "03-30"
                        },
                        {
                            listtitle: "我国古代的“成人”礼仪",
                            time: "03-30"
                        },
                        {
                            listtitle: "从汉字演变看“福””祸”之混",
                            time: "03-30"
                        },
                        {
                            listtitle: "范仲淹:处事莫如为善，传家唯有读书",
                            time: "03-30"
                        },
                        {
                            listtitle: "什么是“八拜之交”、“生死之交”?",
                            time: "03-30"
                        },
                        {
                            listtitle: "动物成语中“昆虫成语”最多",
                            time: "03-30"
                        },
                        {
                            listtitle: "[周易]周易第一卦:乾卦乾为天乾上乾下",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语名句]子夏曰;“博学而笃志，切问而近思，仁在其中矣。”",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语]论语全文带拼音完整版",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语名句]子曰:“吾尝终日不食，终夜不寝，以思，无益，不如学也。”",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语]学而第一",
                            time: "03-10"
                        },
                        {
                            listtitle: "中国端午文化的发源与继承",
                            time: "06-10"
                        },
                        {
                            listtitle: "中药店称为“堂”的典故",
                            time: "05-16"
                        },
                        {
                            listtitle: "墨家的“节用”思想与人性需要之间的矛盾",
                            time: "05-10"
                        },
                        {
                            listtitle: "中国古代文化常识之服饰代称",
                            time: "05-05"
                        },
                        {
                            listtitle: "中国端午文化的发源与继承",
                            time: "04-11"
                        },
                        {
                            listtitle: "《诗经·关雎》中的“河之洲”到底在哪?",
                            time: "04-03"
                        },
                        {
                            listtitle: "寒食已随云影查祭祖无妨踏青游",
                            time: "03-30"
                        },
                        {
                            listtitle: "国学常识之科举制度",
                            time: "03-30"
                        },
                        {
                            listtitle: "儒家何以被称为“百家之首”",
                            time: "03-30"
                        },
                        {
                            listtitle: "书法，让人走向至高境界",
                            time: "03-30"
                        },
                        {
                            listtitle: "认识《黄帝内经》",
                            time: "03-30"
                        },
                        {
                            listtitle: "我国古代的“成人”礼仪",
                            time: "03-30"
                        },
                        {
                            listtitle: "从汉字演变看“福””祸”之混",
                            time: "03-30"
                        },
                        {
                            listtitle: "范仲淹:处事莫如为善，传家唯有读书",
                            time: "03-30"
                        },
                        {
                            listtitle: "什么是“八拜之交”、“生死之交”?",
                            time: "03-30"
                        },
                        {
                            listtitle: "动物成语中“昆虫成语”最多",
                            time: "03-30"
                        },
                        {
                            listtitle: "[周易]周易第一卦:乾卦乾为天乾上乾下",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语名句]子夏曰;“博学而笃志，切问而近思，仁在其中矣。”",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语]论语全文带拼音完整版",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语名句]子曰:“吾尝终日不食，终夜不寝，以思，无益，不如学也。”",
                            time: "03-10"
                        },
                        {
                            listtitle: "[论语]学而第一",
                            time: "03-10"
                        }
                    ],
                    recommand: [
                        {
                            listtitle: "[论语]学而第一"
                        },
                        {
                            listtitle: "[论语名句]子曰:“弟子入则孝，出..."
                        },
                        {
                            listtitle: "[大学]大学全文带拼音"
                        },
                        {
                            listtitle: "[论语名句]子贡曰:“贫而无谄，富..."
                        },
                        {
                            listtitle: "[论语名句]子曰:“《诗》三百，一..."
                        },
                        {
                            listtitle: "[罗织经]阅人卷第一"
                        },
                        {
                            listtitle: "中药店称为“堂”的典故从何而来"
                        },
                        {
                            listtitle: "墨家的“节用”思想与人性需要之间.."
                        },
                        {
                            listtitle: "中国古代文化常识之服饰代称"
                        },
                    ],
                    hot: [
                        {
                            listtitle: "中国端午文化的发源与继承"
                        },
                        {
                            listtitle: "中药店称为“堂”的典故从何而来"
                        },
                        {
                            listtitle: "墨家的“节用”思想与人性需要之间..."
                        },
                        {
                            listtitle: "中国古代文化常识之服饰代称"
                        },
                        {
                            listtitle: "《诗经·关雎》中的“河之洲”到底..."
                        },
                        {
                            listtitle: "国学常识之科举制度"
                        },
                        {
                            listtitle: "儒家何以被称为“百家之首”"
                        },
                        {
                            listtitle: "书法，让人走向至高境界"
                        },
                        {
                            listtitle: "认识《黄帝内经》"
                        },
                        {
                            listtitle: "我国古代的“成人”礼仪"
                        },
                        {
                            listtitle: "从汉字演变看“福””祸”之混"
                        },
                    ]
                },
                {
                    title: "传统节日",
                    descript: "中国传统节日，是中华民族悠久历史文化的重要组成部分，形式多样、内容丰富。传统节日的形成，是一个民族或国家的历史文化长期积淀凝聚的过程。",
                    list: [
                        {
                            listtitle: "元宵节：灯笼和汤圆",
                            time: "06-10"
                        },
                        {
                            listtitle: "清明节：扫墓祭祖",
                            time: "05-16"
                        },
                        {
                            listtitle: "端午节：粽子和龙舟",
                            time: "05-10"
                        },
                        {
                            listtitle: "七夕节：牛郎织女相会",
                            time: "05-05"
                        },
                        {
                            listtitle: "中秋节：团圆和月饼",
                            time: "04-11"
                        },
                        {
                            listtitle: "重阳节：登高赏菊",
                            time: "04-03"
                        },
                        {
                            listtitle: "春节：辞旧迎新",
                            time: "03-30"
                        },
                        {
                            listtitle: "腊八节：喝腊八粥",
                            time: "03-30"
                        },
                        {
                            listtitle: "元旦节：烟花和倒计时",
                            time: "03-30"
                        },
                        {
                            listtitle: "妇女节：赞美女性",
                            time: "03-30"
                        },
                        {
                            listtitle: "儿童节：庆祝孩子们",
                            time: "03-30"
                        },
                        {
                            listtitle: "劳动节：劳动者的节日",
                            time: "03-30"
                        },
                        {
                            listtitle: "国庆节：阅兵和升旗",
                            time: "03-30"
                        },
                        {
                            listtitle: "感恩节：感谢和团聚",
                            time: "03-30"
                        },
                        {
                            listtitle: "情人节：表达爱意",
                            time: "03-30"
                        },
                        {
                            listtitle: "教师节：尊敬教师",
                            time: "03-30"
                        },
                        {
                            listtitle: "护士节：感谢医护人员",
                            time: "03-10"
                        },
                        {
                            listtitle: "光棍节：单身自嘲",
                            time: "03-10"
                        },
                        {
                            listtitle: "圣诞节：圣诞老人和礼物",
                            time: "03-10"
                        },
                        {
                            listtitle: "复活节：复活和彩蛋",
                            time: "03-10"
                        },
                        {
                            listtitle: "澳门回归日：庆祝澳门回归",
                            time: "03-10"
                        },
                        {
                            listtitle: "元宵节：灯笼和汤圆",
                            time: "06-10"
                        },
                        {
                            listtitle: "清明节：扫墓祭祖",
                            time: "05-16"
                        },
                        {
                            listtitle: "端午节：粽子和龙舟",
                            time: "05-10"
                        },
                        {
                            listtitle: "七夕节：牛郎织女相会",
                            time: "05-05"
                        },
                        {
                            listtitle: "中秋节：团圆和月饼",
                            time: "04-11"
                        },
                        {
                            listtitle: "重阳节：登高赏菊",
                            time: "04-03"
                        },
                        {
                            listtitle: "春节：辞旧迎新",
                            time: "03-30"
                        },
                        {
                            listtitle: "腊八节：喝腊八粥",
                            time: "03-30"
                        },
                        {
                            listtitle: "元旦节：烟花和倒计时",
                            time: "03-30"
                        },
                        {
                            listtitle: "妇女节：赞美女性",
                            time: "03-30"
                        },
                        {
                            listtitle: "儿童节：庆祝孩子们",
                            time: "03-30"
                        },
                        {
                            listtitle: "劳动节：劳动者的节日",
                            time: "03-30"
                        },
                        {
                            listtitle: "国庆节：阅兵和升旗",
                            time: "03-30"
                        },
                        {
                            listtitle: "感恩节：感谢和团聚",
                            time: "03-30"
                        },
                        {
                            listtitle: "情人节：表达爱意",
                            time: "03-30"
                        },
                        {
                            listtitle: "教师节：尊敬教师",
                            time: "03-30"
                        },
                        {
                            listtitle: "护士节：感谢医护人员",
                            time: "03-10"
                        },
                        {
                            listtitle: "光棍节：单身自嘲",
                            time: "03-10"
                        },
                        {
                            listtitle: "圣诞节：圣诞老人和礼物",
                            time: "03-10"
                        },
                        {
                            listtitle: "复活节：复活和彩蛋",
                            time: "03-10"
                        },
                        {
                            listtitle: "澳门回归日：庆祝澳门回归",
                            time: "03-10"
                        },
                        {
                            listtitle: "元宵节：灯笼和汤圆",
                            time: "06-10"
                        },
                        {
                            listtitle: "清明节：扫墓祭祖",
                            time: "05-16"
                        },
                        {
                            listtitle: "端午节：粽子和龙舟",
                            time: "05-10"
                        },
                        {
                            listtitle: "七夕节：牛郎织女相会",
                            time: "05-05"
                        },
                        {
                            listtitle: "中秋节：团圆和月饼",
                            time: "04-11"
                        },
                        {
                            listtitle: "重阳节：登高赏菊",
                            time: "04-03"
                        },
                        {
                            listtitle: "春节：辞旧迎新",
                            time: "03-30"
                        },
                        {
                            listtitle: "腊八节：喝腊八粥",
                            time: "03-30"
                        },
                        {
                            listtitle: "元旦节：烟花和倒计时",
                            time: "03-30"
                        },
                        {
                            listtitle: "妇女节：赞美女性",
                            time: "03-30"
                        },
                        {
                            listtitle: "儿童节：庆祝孩子们",
                            time: "03-30"
                        },
                        {
                            listtitle: "劳动节：劳动者的节日",
                            time: "03-30"
                        },
                        {
                            listtitle: "国庆节：阅兵和升旗",
                            time: "03-30"
                        },
                        {
                            listtitle: "感恩节：感谢和团聚",
                            time: "03-30"
                        },
                        {
                            listtitle: "情人节：表达爱意",
                            time: "03-30"
                        },
                        {
                            listtitle: "教师节：尊敬教师",
                            time: "03-30"
                        },
                        {
                            listtitle: "护士节：感谢医护人员",
                            time: "03-10"
                        },
                        {
                            listtitle: "光棍节：单身自嘲",
                            time: "03-10"
                        },
                        {
                            listtitle: "圣诞节：圣诞老人和礼物",
                            time: "03-10"
                        },
                        {
                            listtitle: "复活节：复活和彩蛋",
                            time: "03-10"
                        },
                        {
                            listtitle: "澳门回归日：庆祝澳门回归",
                            time: "03-10"
                        },
                        {
                            listtitle: "元宵节：灯笼和汤圆",
                            time: "06-10"
                        },
                        {
                            listtitle: "清明节：扫墓祭祖",
                            time: "05-16"
                        },
                        {
                            listtitle: "端午节：粽子和龙舟",
                            time: "05-10"
                        },
                        {
                            listtitle: "七夕节：牛郎织女相会",
                            time: "05-05"
                        },
                        {
                            listtitle: "中秋节：团圆和月饼",
                            time: "04-11"
                        },
                        {
                            listtitle: "重阳节：登高赏菊",
                            time: "04-03"
                        },
                        {
                            listtitle: "春节：辞旧迎新",
                            time: "03-30"
                        },
                        {
                            listtitle: "腊八节：喝腊八粥",
                            time: "03-30"
                        },
                        {
                            listtitle: "元旦节：烟花和倒计时",
                            time: "03-30"
                        },
                        {
                            listtitle: "妇女节：赞美女性",
                            time: "03-30"
                        },
                        {
                            listtitle: "儿童节：庆祝孩子们",
                            time: "03-30"
                        },
                        {
                            listtitle: "劳动节：劳动者的节日",
                            time: "03-30"
                        },
                        {
                            listtitle: "国庆节：阅兵和升旗",
                            time: "03-30"
                        },
                        {
                            listtitle: "感恩节：感谢和团聚",
                            time: "03-30"
                        },
                        {
                            listtitle: "情人节：表达爱意",
                            time: "03-30"
                        },
                        {
                            listtitle: "教师节：尊敬教师",
                            time: "03-30"
                        },
                        {
                            listtitle: "护士节：感谢医护人员",
                            time: "03-10"
                        },
                        {
                            listtitle: "光棍节：单身自嘲",
                            time: "03-10"
                        },
                        {
                            listtitle: "圣诞节：圣诞老人和礼物",
                            time: "03-10"
                        },
                        {
                            listtitle: "复活节：复活和彩蛋",
                            time: "03-10"
                        },
                        {
                            listtitle: "澳门回归日：庆祝澳门回归",
                            time: "03-10"
                        },
                    ],
                    recommand: [
                        {
                            listtitle: "元宵节：灯笼和汤圆"
                        },
                        {
                            listtitle: "清明节：扫墓祭祖"
                        },
                        {
                            listtitle: "端午节：粽子和龙舟"
                        },
                        {
                            listtitle: "七夕节：牛郎织女相会"
                        },
                        {
                            listtitle: "中秋节：团圆和月饼"
                        },
                        {
                            listtitle: "重阳节：登高赏菊"
                        },
                        {
                            listtitle: "春节：辞旧迎新"
                        },
                        {
                            listtitle: "腊八节：喝腊八粥"
                        },
                        {
                            listtitle: "元旦节：烟花和倒计时"
                        },
                    ],
                    hot: [
                        {
                            listtitle: "元宵节：灯笼和汤圆"
                        },
                        {
                            listtitle: "清明节：扫墓祭祖"
                        },
                        {
                            listitle: "端午节：粽子和龙舟"
                        },
                        {
                            listtitle: "七夕节：牛郎织女相会"
                        },
                        {
                            listtitle: "中秋节：团圆和月饼"
                        },
                        {
                            listtitle: "重阳节：登高赏菊"
                        },
                        {
                            listtitle: "春节：辞旧迎新"
                        },
                        {
                            listtitle: "腊八节：喝腊八粥"
                        },
                        {
                            listtitle: "元旦节：烟花和倒计时"
                        },
                        {
                            listtitle: "复活节：复活和彩蛋",
                            time: "03-10"
                        },
                        {
                            listtitle: "澳门回归日：庆祝澳门回归",
                            time: "03-10"
                        },
                    ]
                },
                {
                    title: "健康文化",
                    descript: "健康文化是中华文化的重要组成部分，是以协调人与自然和疾病斗争为核心，在防治疾病、维护和增进健康的实践过程中所形成的精神成果与物质成果的总和。",
                    list: [
                        {
                            listtitle: "晨跑：每天晨跑健康生活",
                            time: "06-10"
                        },
                        {
                            listtitle: "青菜汤：补充维生素",
                            time: "05-16"
                        },
                        {
                            listtitle: "红糖姜水：驱寒保暖",
                            time: "05-10"
                        },
                        {
                            listtitle: "豆浆：健康饮品",
                            time: "05-05"
                        },
                        {
                            listtitle: "瑜伽：舒展身心",
                            time: "04-11"
                        },
                        {
                            listtitle: "薏米水：清热利湿",
                            time: "04-03"
                        },
                        {
                            listtitle: "芝麻糊：养生美容",
                            time: "03-30"
                        },
                        {
                            listtitle: "姜黄水：消炎抗菌",
                            time: "03-30"
                        },
                        {
                            listtitle: "零食断食：减肥养生",
                            time: "03-30"
                        },
                        {
                            listtitle: "酸奶：益生菌养生",
                            time: "03-30"
                        },
                        {
                            listtitle: "健康饮食：营养均衡",
                            time: "03-30"
                        },
                        {
                            listtitle: "药膳煲汤：滋阴补肾",
                            time: "03-30"
                        },
                        {
                            listtitle: "中药养生：治未病",
                            time: "03-30"
                        },
                        {
                            listtitle: "知识普及：健康自救",
                            time: "03-30"
                        },
                        {
                            listtitle: "医学知识：识别常见疾病",
                            time: "03-30"
                        },
                        {
                            listtitle: "生鲜食材：健康饮食的基础",
                            time: "03-30"
                        },
                        {
                            listtitle: "刷牙：口腔健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "睡眠：良好睡眠有助于身心健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "运动：有氧运动健康生活",
                            time: "03-10"
                        },
                        {
                            listtitle: "心理健康：良好心态关键健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "晨跑：每天晨跑健康生活",
                            time: "06-10"
                        },
                        {
                            listtitle: "青菜汤：补充维生素",
                            time: "05-16"
                        },
                        {
                            listtitle: "红糖姜水：驱寒保暖",
                            time: "05-10"
                        },
                        {
                            listtitle: "豆浆：健康饮品",
                            time: "05-05"
                        },
                        {
                            listtitle: "瑜伽：舒展身心",
                            time: "04-11"
                        },
                        {
                            listtitle: "薏米水：清热利湿",
                            time: "04-03"
                        },
                        {
                            listtitle: "芝麻糊：养生美容",
                            time: "03-30"
                        },
                        {
                            listtitle: "姜黄水：消炎抗菌",
                            time: "03-30"
                        },
                        {
                            listtitle: "零食断食：减肥养生",
                            time: "03-30"
                        },
                        {
                            listtitle: "酸奶：益生菌养生",
                            time: "03-30"
                        },
                        {
                            listtitle: "健康饮食：营养均衡",
                            time: "03-30"
                        },
                        {
                            listtitle: "药膳煲汤：滋阴补肾",
                            time: "03-30"
                        },
                        {
                            listtitle: "中药养生：治未病",
                            time: "03-30"
                        },
                        {
                            listtitle: "知识普及：健康自救",
                            time: "03-30"
                        },
                        {
                            listtitle: "医学知识：识别常见疾病",
                            time: "03-30"
                        },
                        {
                            listtitle: "生鲜食材：健康饮食的基础",
                            time: "03-30"
                        },
                        {
                            listtitle: "刷牙：口腔健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "睡眠：良好睡眠有助于身心健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "运动：有氧运动健康生活",
                            time: "03-10"
                        },
                        {
                            listtitle: "心理健康：良好心态关键健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "晨跑：每天晨跑健康生活",
                            time: "06-10"
                        },
                        {
                            listtitle: "青菜汤：补充维生素",
                            time: "05-16"
                        },
                        {
                            listtitle: "红糖姜水：驱寒保暖",
                            time: "05-10"
                        },
                        {
                            listtitle: "豆浆：健康饮品",
                            time: "05-05"
                        },
                        {
                            listtitle: "瑜伽：舒展身心",
                            time: "04-11"
                        },
                        {
                            listtitle: "薏米水：清热利湿",
                            time: "04-03"
                        },
                        {
                            listtitle: "芝麻糊：养生美容",
                            time: "03-30"
                        },
                        {
                            listtitle: "姜黄水：消炎抗菌",
                            time: "03-30"
                        },
                        {
                            listtitle: "零食断食：减肥养生",
                            time: "03-30"
                        },
                        {
                            listtitle: "酸奶：益生菌养生",
                            time: "03-30"
                        },
                        {
                            listtitle: "健康饮食：营养均衡",
                            time: "03-30"
                        },
                        {
                            listtitle: "药膳煲汤：滋阴补肾",
                            time: "03-30"
                        },
                        {
                            listtitle: "中药养生：治未病",
                            time: "03-30"
                        },
                        {
                            listtitle: "知识普及：健康自救",
                            time: "03-30"
                        },
                        {
                            listtitle: "医学知识：识别常见疾病",
                            time: "03-30"
                        },
                        {
                            listtitle: "生鲜食材：健康饮食的基础",
                            time: "03-30"
                        },
                        {
                            listtitle: "刷牙：口腔健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "睡眠：良好睡眠有助于身心健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "运动：有氧运动健康生活",
                            time: "03-10"
                        },
                        {
                            listtitle: "心理健康：良好心态关键健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "晨跑：每天晨跑健康生活",
                            time: "06-10"
                        },
                        {
                            listtitle: "青菜汤：补充维生素",
                            time: "05-16"
                        },
                        {
                            listtitle: "红糖姜水：驱寒保暖",
                            time: "05-10"
                        },
                        {
                            listtitle: "豆浆：健康饮品",
                            time: "05-05"
                        },
                        {
                            listtitle: "瑜伽：舒展身心",
                            time: "04-11"
                        },
                        {
                            listtitle: "薏米水：清热利湿",
                            time: "04-03"
                        },
                        {
                            listtitle: "芝麻糊：养生美容",
                            time: "03-30"
                        },
                        {
                            listtitle: "姜黄水：消炎抗菌",
                            time: "03-30"
                        },
                        {
                            listtitle: "零食断食：减肥养生",
                            time: "03-30"
                        },
                        {
                            listtitle: "酸奶：益生菌养生",
                            time: "03-30"
                        },
                        {
                            listtitle: "健康饮食：营养均衡",
                            time: "03-30"
                        },
                        {
                            listtitle: "药膳煲汤：滋阴补肾",
                            time: "03-30"
                        },
                        {
                            listtitle: "中药养生：治未病",
                            time: "03-30"
                        },
                        {
                            listtitle: "知识普及：健康自救",
                            time: "03-30"
                        },
                        {
                            listtitle: "医学知识：识别常见疾病",
                            time: "03-30"
                        },
                        {
                            listtitle: "生鲜食材：健康饮食的基础",
                            time: "03-30"
                        },
                        {
                            listtitle: "刷牙：口腔健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "睡眠：良好睡眠有助于身心健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "运动：有氧运动健康生活",
                            time: "03-10"
                        },
                        {
                            listtitle: "心理健康：良好心态关键健康",
                            time: "03-10"
                        },
                    ],
                    recommand: [
                        {
                            listtitle: "药膳煲汤：滋阴补肾",
                            time: "03-30"
                        },
                        {
                            listtitle: "中药养生：治未病",
                            time: "03-30"
                        },
                        {
                            listtitle: "知识普及：健康自救",
                            time: "03-30"
                        },
                        {
                            listtitle: "医学知识：识别常见疾病",
                            time: "03-30"
                        },
                        {
                            listtitle: "生鲜食材：健康饮食的基础",
                            time: "03-30"
                        },
                        {
                            listtitle: "刷牙：口腔健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "睡眠：良好睡眠有助于身心健康",
                            time: "03-10"
                        },
                        {
                            listtitle: "运动：有氧运动健康生活",
                            time: "03-10"
                        },
                        {
                            listtitle: "心理健康：良好心态关键健康",
                            time: "03-10"
                        },
                    ],
                    hot: [
                        {
                            listtitle: "晨跑：每天晨跑健康生活",
                            time: "06-10"
                        },
                        {
                            listtitle: "青菜汤：补充维生素",
                            time: "05-16"
                        },
                        {
                            listtitle: "红糖姜水：驱寒保暖",
                            time: "05-10"
                        },
                        {
                            listtitle: "豆浆：健康饮品",
                            time: "05-05"
                        },
                        {
                            listtitle: "瑜伽：舒展身心",
                            time: "04-11"
                        },
                        {
                            listtitle: "薏米水：清热利湿",
                            time: "04-03"
                        },
                        {
                            listtitle: "芝麻糊：养生美容",
                            time: "03-30"
                        },
                        {
                            listtitle: "姜黄水：消炎抗菌",
                            time: "03-30"
                        },
                        {
                            listtitle: "零食断食：减肥养生",
                            time: "03-30"
                        },
                        {
                            listtitle: "酸奶：益生菌养生",
                            time: "03-30"
                        },
                        {
                            listtitle: "健康饮食：营养均衡",
                            time: "03-30"
                        },
                    ]
                },
                {
                    title: "人文地理",
                    descript: "人文地理学一般有广义与狭义之分，广义的人文地理学包括社会文化地理学、政治地理学、经济地理学等，狭义的人文地理学则指社会文化地理学，不包括经济地理学。",
                    list: [
                        {
                            listtitle: "丝绸之路：古代商路文化",
                            time: "06-10"
                        },
                        {
                            listtitle: "黄河文明：华夏文化的发源地",
                            time: "05-16"
                        },
                        {
                            listtitle: "大峡谷：绝美自然风光",
                            time: "05-10"
                        },
                        {
                            listtitle: "巨石阵：神秘的史前遗迹",
                            time: "05-05"
                        },
                        {
                            listtitle: "城市记忆：现代都市文化",
                            time: "04-11"
                        },
                        {
                            listtitle: "敦煌壁画：古代艺术珍品",
                            time: "04-03"
                        },
                        {
                            listtitle: "冰川雪山：自然的奇观",
                            time: "03-30"
                        },
                        {
                            listtitle: "气候变化：人类面临的挑战",
                            time: "03-30"
                        },
                        {
                            listtitle: "古村落：传统建筑文化",
                            time: "03-30"
                        },
                        {
                            listtitle: "沙漠风情：另一种自然美",
                            time: "03-30"
                        },
                        {
                            listtitle: "认识《黄帝内经》",
                            time: "03-30"
                        },
                        {
                            listtitle: "特色美食：地域饮食文化",
                            time: "03-30"
                        },
                        {
                            listtitle: "水乡古镇：水文化与历史文化融合",
                            time: "03-30"
                        },
                        {
                            listtitle: "西湖：文学与浪漫相融合",
                            time: "03-30"
                        },
                        {
                            listtitle: "天坑地缝：地质奇观",
                            time: "03-30"
                        },
                        {
                            listtitle: "生态保护：自然资源的可持续利用",
                            time: "03-30"
                        },
                        {
                            listtitle: "水利文化：古代水利工程的技术创新和文化传承",
                            time: "03-10"
                        },
                        {
                            listtitle: "渔民岛屿：人与自然共生的微缩图景",
                            time: "03-10"
                        },
                        {
                            listtitle: "海上丝绸之路：古代“一带一路”实践",
                            time: "03-10"
                        },
                        {
                            listtitle: "水墨山水：中国绘画文化的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "神秘岩画：史前文化的宝库",
                            time: "03-10"
                        },
                        {
                            listtitle: "丝绸之路：古代商路文化",
                            time: "06-10"
                        },
                        {
                            listtitle: "黄河文明：华夏文化的发源地",
                            time: "05-16"
                        },
                        {
                            listtitle: "大峡谷：绝美自然风光",
                            time: "05-10"
                        },
                        {
                            listtitle: "巨石阵：神秘的史前遗迹",
                            time: "05-05"
                        },
                        {
                            listtitle: "城市记忆：现代都市文化",
                            time: "04-11"
                        },
                        {
                            listtitle: "敦煌壁画：古代艺术珍品",
                            time: "04-03"
                        },
                        {
                            listtitle: "冰川雪山：自然的奇观",
                            time: "03-30"
                        },
                        {
                            listtitle: "气候变化：人类面临的挑战",
                            time: "03-30"
                        },
                        {
                            listtitle: "古村落：传统建筑文化",
                            time: "03-30"
                        },
                        {
                            listtitle: "沙漠风情：另一种自然美",
                            time: "03-30"
                        },
                        {
                            listtitle: "认识《黄帝内经》",
                            time: "03-30"
                        },
                        {
                            listtitle: "特色美食：地域饮食文化",
                            time: "03-30"
                        },
                        {
                            listtitle: "水乡古镇：水文化与历史文化融合",
                            time: "03-30"
                        },
                        {
                            listtitle: "西湖：文学与浪漫相融合",
                            time: "03-30"
                        },
                        {
                            listtitle: "天坑地缝：地质奇观",
                            time: "03-30"
                        },
                        {
                            listtitle: "生态保护：自然资源的可持续利用",
                            time: "03-30"
                        },
                        {
                            listtitle: "水利文化：古代水利工程的技术创新和文化传承",
                            time: "03-10"
                        },
                        {
                            listtitle: "渔民岛屿：人与自然共生的微缩图景",
                            time: "03-10"
                        },
                        {
                            listtitle: "海上丝绸之路：古代“一带一路”实践",
                            time: "03-10"
                        },
                        {
                            listtitle: "水墨山水：中国绘画文化的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "神秘岩画：史前文化的宝库",
                            time: "03-10"
                        },
                        {
                            listtitle: "丝绸之路：古代商路文化",
                            time: "06-10"
                        },
                        {
                            listtitle: "黄河文明：华夏文化的发源地",
                            time: "05-16"
                        },
                        {
                            listtitle: "大峡谷：绝美自然风光",
                            time: "05-10"
                        },
                        {
                            listtitle: "巨石阵：神秘的史前遗迹",
                            time: "05-05"
                        },
                        {
                            listtitle: "城市记忆：现代都市文化",
                            time: "04-11"
                        },
                        {
                            listtitle: "敦煌壁画：古代艺术珍品",
                            time: "04-03"
                        },
                        {
                            listtitle: "冰川雪山：自然的奇观",
                            time: "03-30"
                        },
                        {
                            listtitle: "气候变化：人类面临的挑战",
                            time: "03-30"
                        },
                        {
                            listtitle: "古村落：传统建筑文化",
                            time: "03-30"
                        },
                        {
                            listtitle: "沙漠风情：另一种自然美",
                            time: "03-30"
                        },
                        {
                            listtitle: "认识《黄帝内经》",
                            time: "03-30"
                        },
                        {
                            listtitle: "特色美食：地域饮食文化",
                            time: "03-30"
                        },
                        {
                            listtitle: "水乡古镇：水文化与历史文化融合",
                            time: "03-30"
                        },
                        {
                            listtitle: "西湖：文学与浪漫相融合",
                            time: "03-30"
                        },
                        {
                            listtitle: "天坑地缝：地质奇观",
                            time: "03-30"
                        },
                        {
                            listtitle: "生态保护：自然资源的可持续利用",
                            time: "03-30"
                        },
                        {
                            listtitle: "水利文化：古代水利工程的技术创新和文化传承",
                            time: "03-10"
                        },
                        {
                            listtitle: "渔民岛屿：人与自然共生的微缩图景",
                            time: "03-10"
                        },
                        {
                            listtitle: "海上丝绸之路：古代“一带一路”实践",
                            time: "03-10"
                        },
                        {
                            listtitle: "水墨山水：中国绘画文化的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "神秘岩画：史前文化的宝库",
                            time: "03-10"
                        },
                        {
                            listtitle: "丝绸之路：古代商路文化",
                            time: "06-10"
                        },
                        {
                            listtitle: "黄河文明：华夏文化的发源地",
                            time: "05-16"
                        },
                        {
                            listtitle: "大峡谷：绝美自然风光",
                            time: "05-10"
                        },
                        {
                            listtitle: "巨石阵：神秘的史前遗迹",
                            time: "05-05"
                        },
                        {
                            listtitle: "城市记忆：现代都市文化",
                            time: "04-11"
                        },
                        {
                            listtitle: "敦煌壁画：古代艺术珍品",
                            time: "04-03"
                        },
                        {
                            listtitle: "冰川雪山：自然的奇观",
                            time: "03-30"
                        },
                        {
                            listtitle: "气候变化：人类面临的挑战",
                            time: "03-30"
                        },
                        {
                            listtitle: "古村落：传统建筑文化",
                            time: "03-30"
                        },
                        {
                            listtitle: "沙漠风情：另一种自然美",
                            time: "03-30"
                        },
                        {
                            listtitle: "认识《黄帝内经》",
                            time: "03-30"
                        },
                        {
                            listtitle: "特色美食：地域饮食文化",
                            time: "03-30"
                        },
                        {
                            listtitle: "水乡古镇：水文化与历史文化融合",
                            time: "03-30"
                        },
                        {
                            listtitle: "西湖：文学与浪漫相融合",
                            time: "03-30"
                        },
                        {
                            listtitle: "天坑地缝：地质奇观",
                            time: "03-30"
                        },
                        {
                            listtitle: "生态保护：自然资源的可持续利用",
                            time: "03-30"
                        },
                        {
                            listtitle: "水利文化：古代水利工程的技术创新和文化传承",
                            time: "03-10"
                        },
                        {
                            listtitle: "渔民岛屿：人与自然共生的微缩图景",
                            time: "03-10"
                        },
                        {
                            listtitle: "海上丝绸之路：古代“一带一路”实践",
                            time: "03-10"
                        },
                        {
                            listtitle: "水墨山水：中国绘画文化的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "神秘岩画：史前文化的宝库",
                            time: "03-10"
                        },
                    ],
                    recommand: [
                        {
                            listtitle: "西湖：文学与浪漫相融合",
                            time: "03-30"
                        },
                        {
                            listtitle: "天坑地缝：地质奇观",
                            time: "03-30"
                        },
                        {
                            listtitle: "生态保护：自然资源的可持续利用",
                            time: "03-30"
                        },
                        {
                            listtitle: "水利文化：古代水利工程的技术创新和文化传承",
                            time: "03-10"
                        },
                        {
                            listtitle: "渔民岛屿：人与自然共生的微缩图景",
                            time: "03-10"
                        },
                        {
                            listtitle: "海上丝绸之路：古代“一带一路”实践",
                            time: "03-10"
                        },
                        {
                            listtitle: "水墨山水：中国绘画文化的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "神秘岩画：史前文化的宝库",
                            time: "03-10"
                        },
                        {
                            listtitle: "沙漠风情：另一种自然美",
                            time: "03-30"
                        },
                    ],
                    hot: [
                        {
                            listtitle: "丝绸之路：古代商路文化",
                            time: "06-10"
                        },
                        {
                            listtitle: "黄河文明：华夏文化的发源地",
                            time: "05-16"
                        },
                        {
                            listtitle: "大峡谷：绝美自然风光",
                            time: "05-10"
                        },
                        {
                            listtitle: "巨石阵：神秘的史前遗迹",
                            time: "05-05"
                        },
                        {
                            listtitle: "城市记忆：现代都市文化",
                            time: "04-11"
                        },
                        {
                            listtitle: "敦煌壁画：古代艺术珍品",
                            time: "04-03"
                        },
                        {
                            listtitle: "冰川雪山：自然的奇观",
                            time: "03-30"
                        },
                        {
                            listtitle: "气候变化：人类面临的挑战",
                            time: "03-30"
                        },
                        {
                            listtitle: "古村落：传统建筑文化",
                            time: "03-30"
                        },
                        {
                            listtitle: "沙漠风情：另一种自然美",
                            time: "03-30"
                        },
                        {
                            listtitle: "认识《黄帝内经》",
                            time: "03-30"
                        },
                    ]
                },
                {
                    title: "文学艺术",
                    descript: "文学艺术(literature and art)是属于艺术范畴的文学，是利用文字表达的一种语言艺术。而艺术泛指一切借助语言、表演、造型等手段形象地反映客观世界和表达主观情感的文化。",
                    list: [
                        {
                            listtitle: "古典诗词：华夏文化的瑰宝",
                            time: "06-10"
                        },
                        {
                            listtitle: "魏晋风度：古时文人雅士的精神风貌",
                            time: "05-16"
                        },
                        {
                            listtitle: "文学经典：历史与人性的结晶",
                            time: "05-10"
                        },
                        {
                            listtitle: "京剧：中国皮影戏和曲艺的经典",
                            time: "05-05"
                        },
                        {
                            listtitle: "民间艺术：传统与创新的碰撞",
                            time: "04-11"
                        },
                        {
                            listtitle: "书法篆刻：字体美学的升华",
                            time: "04-03"
                        },
                        {
                            listtitle: "四大名著：中国小说文化的巅峰之作",
                            time: "03-30"
                        },
                        {
                            listtitle: "漫画动画：视觉文化的魅力",
                            time: "03-30"
                        },
                        {
                            listtitle: "京杭大运河：水路文化的演化之路”",
                            time: "03-30"
                        },
                        {
                            listtitle: "书法，让人走向至高境界",
                            time: "03-30"
                        },
                        {
                            listtitle: "千里江山图：绘画艺术的陈述之语",
                            time: "03-30"
                        },
                        {
                            listtitle: "武侠小说：古代侠客精神的体现",
                            time: "03-30"
                        },
                        {
                            listtitle: "民间传说：历史的印记与文化的传承",
                            time: "03-30"
                        },
                        {
                            listtitle: "电影文化：镜头下的社会变迁",
                            time: "03-30"
                        },
                        {
                            listtitle: "书店文化：知识启蒙与文化传播的重要载体",
                            time: "03-30"
                        },
                        {
                            listtitle: "诗经：中国文化最古老的诗歌总集",
                            time: "03-10"
                        },
                        {
                            listtitle: "水墨画：东方美学艺术的独特表现",
                            time: "03-10"
                        },
                        {
                            listtitle: "口碑文化：口口相传的文化传统",
                            time: "03-10"
                        },
                        {
                            listtitle: "明清小说：社会变迁下文学的发展",
                            time: "03-10"
                        },
                        {
                            listtitle: "童话故事：童心和想象力的无限延伸",
                            time: "03-10"
                        },
                        {
                            listtitle: "沧浪亭对联：品味古代文人雅士的魅力",
                            time: "06-10"
                        },
                        {
                            listtitle: "中外合作：文化交流的新模式",
                            time: "05-16"
                        },
                        {
                            listtitle: "古典诗词：华夏文化的瑰宝",
                            time: "06-10"
                        },
                        {
                            listtitle: "魏晋风度：古时文人雅士的精神风貌",
                            time: "05-16"
                        },
                        {
                            listtitle: "文学经典：历史与人性的结晶",
                            time: "05-10"
                        },
                        {
                            listtitle: "京剧：中国皮影戏和曲艺的经典",
                            time: "05-05"
                        },
                        {
                            listtitle: "民间艺术：传统与创新的碰撞",
                            time: "04-11"
                        },
                        {
                            listtitle: "书法篆刻：字体美学的升华",
                            time: "04-03"
                        },
                        {
                            listtitle: "四大名著：中国小说文化的巅峰之作",
                            time: "03-30"
                        },
                        {
                            listtitle: "漫画动画：视觉文化的魅力",
                            time: "03-30"
                        },
                        {
                            listtitle: "京杭大运河：水路文化的演化之路”",
                            time: "03-30"
                        },
                        {
                            listtitle: "书法，让人走向至高境界",
                            time: "03-30"
                        },
                        {
                            listtitle: "千里江山图：绘画艺术的陈述之语",
                            time: "03-30"
                        },
                        {
                            listtitle: "武侠小说：古代侠客精神的体现",
                            time: "03-30"
                        },
                        {
                            listtitle: "民间传说：历史的印记与文化的传承",
                            time: "03-30"
                        },
                        {
                            listtitle: "电影文化：镜头下的社会变迁",
                            time: "03-30"
                        },
                        {
                            listtitle: "书店文化：知识启蒙与文化传播的重要载体",
                            time: "03-30"
                        },
                        {
                            listtitle: "诗经：中国文化最古老的诗歌总集",
                            time: "03-10"
                        },
                        {
                            listtitle: "水墨画：东方美学艺术的独特表现",
                            time: "03-10"
                        },
                        {
                            listtitle: "口碑文化：口口相传的文化传统",
                            time: "03-10"
                        },
                        {
                            listtitle: "明清小说：社会变迁下文学的发展",
                            time: "03-10"
                        },
                        {
                            listtitle: "童话故事：童心和想象力的无限延伸",
                            time: "03-10"
                        },
                        {
                            listtitle: "沧浪亭对联：品味古代文人雅士的魅力",
                            time: "06-10"
                        },
                        {
                            listtitle: "中外合作：文化交流的新模式",
                            time: "05-16"
                        },
                        {
                            listtitle: "古典诗词：华夏文化的瑰宝",
                            time: "06-10"
                        },
                        {
                            listtitle: "魏晋风度：古时文人雅士的精神风貌",
                            time: "05-16"
                        },
                        {
                            listtitle: "文学经典：历史与人性的结晶",
                            time: "05-10"
                        },
                        {
                            listtitle: "京剧：中国皮影戏和曲艺的经典",
                            time: "05-05"
                        },
                        {
                            listtitle: "民间艺术：传统与创新的碰撞",
                            time: "04-11"
                        },
                        {
                            listtitle: "书法篆刻：字体美学的升华",
                            time: "04-03"
                        },
                        {
                            listtitle: "四大名著：中国小说文化的巅峰之作",
                            time: "03-30"
                        },
                        {
                            listtitle: "漫画动画：视觉文化的魅力",
                            time: "03-30"
                        },
                        {
                            listtitle: "京杭大运河：水路文化的演化之路”",
                            time: "03-30"
                        },
                        {
                            listtitle: "书法，让人走向至高境界",
                            time: "03-30"
                        },
                        {
                            listtitle: "千里江山图：绘画艺术的陈述之语",
                            time: "03-30"
                        },
                        {
                            listtitle: "武侠小说：古代侠客精神的体现",
                            time: "03-30"
                        },
                        {
                            listtitle: "民间传说：历史的印记与文化的传承",
                            time: "03-30"
                        },
                        {
                            listtitle: "电影文化：镜头下的社会变迁",
                            time: "03-30"
                        },
                        {
                            listtitle: "书店文化：知识启蒙与文化传播的重要载体",
                            time: "03-30"
                        },
                        {
                            listtitle: "诗经：中国文化最古老的诗歌总集",
                            time: "03-10"
                        },
                        {
                            listtitle: "水墨画：东方美学艺术的独特表现",
                            time: "03-10"
                        },
                        {
                            listtitle: "口碑文化：口口相传的文化传统",
                            time: "03-10"
                        },
                        {
                            listtitle: "明清小说：社会变迁下文学的发展",
                            time: "03-10"
                        },
                        {
                            listtitle: "童话故事：童心和想象力的无限延伸",
                            time: "03-10"
                        },
                        {
                            listtitle: "沧浪亭对联：品味古代文人雅士的魅力",
                            time: "06-10"
                        },
                        {
                            listtitle: "中外合作：文化交流的新模式",
                            time: "05-16"
                        },
                        {
                            listtitle: "古典诗词：华夏文化的瑰宝",
                            time: "06-10"
                        },
                        {
                            listtitle: "魏晋风度：古时文人雅士的精神风貌",
                            time: "05-16"
                        },
                        {
                            listtitle: "文学经典：历史与人性的结晶",
                            time: "05-10"
                        },
                        {
                            listtitle: "京剧：中国皮影戏和曲艺的经典",
                            time: "05-05"
                        },
                        {
                            listtitle: "民间艺术：传统与创新的碰撞",
                            time: "04-11"
                        },
                        {
                            listtitle: "书法篆刻：字体美学的升华",
                            time: "04-03"
                        },
                        {
                            listtitle: "四大名著：中国小说文化的巅峰之作",
                            time: "03-30"
                        },
                        {
                            listtitle: "漫画动画：视觉文化的魅力",
                            time: "03-30"
                        },
                        {
                            listtitle: "京杭大运河：水路文化的演化之路”",
                            time: "03-30"
                        },
                        {
                            listtitle: "书法，让人走向至高境界",
                            time: "03-30"
                        },
                        {
                            listtitle: "千里江山图：绘画艺术的陈述之语",
                            time: "03-30"
                        },
                        {
                            listtitle: "武侠小说：古代侠客精神的体现",
                            time: "03-30"
                        },
                        {
                            listtitle: "民间传说：历史的印记与文化的传承",
                            time: "03-30"
                        },
                        {
                            listtitle: "电影文化：镜头下的社会变迁",
                            time: "03-30"
                        },
                        {
                            listtitle: "书店文化：知识启蒙与文化传播的重要载体",
                            time: "03-30"
                        },
                        {
                            listtitle: "诗经：中国文化最古老的诗歌总集",
                            time: "03-10"
                        },
                        {
                            listtitle: "水墨画：东方美学艺术的独特表现",
                            time: "03-10"
                        },
                        {
                            listtitle: "口碑文化：口口相传的文化传统",
                            time: "03-10"
                        },
                        {
                            listtitle: "明清小说：社会变迁下文学的发展",
                            time: "03-10"
                        },
                        {
                            listtitle: "童话故事：童心和想象力的无限延伸",
                            time: "03-10"
                        },
                        {
                            listtitle: "沧浪亭对联：品味古代文人雅士的魅力",
                            time: "06-10"
                        },
                        {
                            listtitle: "中外合作：文化交流的新模式",
                            time: "05-16"
                        },
                    ],
                    recommand: [
                        {
                            listtitle: "电影文化：镜头下的社会变迁",
                            time: "03-30"
                        },
                        {
                            listtitle: "书店文化：知识启蒙与文化传播的重要载体",
                            time: "03-30"
                        },
                        {
                            listtitle: "诗经：中国文化最古老的诗歌总集",
                            time: "03-10"
                        },
                        {
                            listtitle: "水墨画：东方美学艺术的独特表现",
                            time: "03-10"
                        },
                        {
                            listtitle: "口碑文化：口口相传的文化传统",
                            time: "03-10"
                        },
                        {
                            listtitle: "明清小说：社会变迁下文学的发展",
                            time: "03-10"
                        },
                        {
                            listtitle: "童话故事：童心和想象力的无限延伸",
                            time: "03-10"
                        },
                        {
                            listtitle: "沧浪亭对联：品味古代文人雅士的魅力",
                            time: "06-10"
                        },
                        {
                            listtitle: "中外合作：文化交流的新模式",
                            time: "05-16"
                        },
                    ],
                    hot: [
                        {
                            listtitle: "古典诗词：华夏文化的瑰宝",
                            time: "06-10"
                        },
                        {
                            listtitle: "魏晋风度：古时文人雅士的精神风貌",
                            time: "05-16"
                        },
                        {
                            listtitle: "文学经典：历史与人性的结晶",
                            time: "05-10"
                        },
                        {
                            listtitle: "京剧：中国皮影戏和曲艺的经典",
                            time: "05-05"
                        },
                        {
                            listtitle: "民间艺术：传统与创新的碰撞",
                            time: "04-11"
                        },
                        {
                            listtitle: "书法篆刻：字体美学的升华",
                            time: "04-03"
                        },
                        {
                            listtitle: "四大名著：中国小说文化的巅峰之作",
                            time: "03-30"
                        },
                        {
                            listtitle: "漫画动画：视觉文化的魅力",
                            time: "03-30"
                        },
                        {
                            listtitle: "京杭大运河：水路文化的演化之路”",
                            time: "03-30"
                        },
                        {
                            listtitle: "书法，让人走向至高境界",
                            time: "03-30"
                        },
                        {
                            listtitle: "千里江山图：绘画艺术的陈述之语",
                            time: "03-30"
                        },
                    ]
                },
                {
                    title: "华夏历史",
                    descript: "华夏，也称“华”、“夏” 或 “诸夏”等。“华夏”一词最早见于《尚书·周书·武成》：“华夏蛮貊，罔不率俾。”从考古来看，华的概念与仰韶文化有关。",
                    list: [
                        {
                            listtitle: "夏商周：三千年前的历史记忆",
                            time: "06-10"
                        },
                        {
                            listtitle: "秦汉帝国：统一中华大地的历史巨人",
                            time: "05-16"
                        },
                        {
                            listtitle: "唐宋元明清：中国历史文化的显著时期",
                            time: "05-10"
                        },
                        {
                            listtitle: "中华民族：多元文化融合的民族群体",
                            time: "05-05"
                        },
                        {
                            listtitle: "四大发明：科技进步带动文化推广",
                            time: "04-11"
                        },
                        {
                            listtitle: "丝绸、茶叶、瓷器：华夏文化的代表物品",
                            time: "04-03"
                        },
                        {
                            listtitle: "长江、黄河、珠江：祖国母亲的三大江河",
                            time: "03-30"
                        },
                        {
                            listtitle: "资治通鉴：中国历史上的一部巨著",
                            time: "03-30"
                        },
                        {
                            listtitle: "东方红：中国历史上的人造卫星",
                            time: "03-30"
                        },
                        {
                            listtitle: "贸易通商：古代“一带一路”先河",
                            time: "03-30"
                        },
                        {
                            listtitle: "古代遗址：走进祖先的历史足迹",
                            time: "03-30"
                        },
                        {
                            listtitle: "清明上河图：描述古代都市生活的名画",
                            time: "03-30"
                        },
                        {
                            listtitle: "长城万里：中华民族的历史丰碑",
                            time: "03-30"
                        },
                        {
                            listtitle: "敦煌石窟：唐代壁画艺术的代表",
                            time: "03-30"
                        },
                        {
                            listtitle: "儒家文化：中国哲学思想的重要流派",
                            time: "03-30"
                        },
                        {
                            listtitle: "家谱文化：家族历史和文化的传承",
                            time: "03-30"
                        },
                        {
                            listtitle: "饮茶文化：社交与休闲文化的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "国宝级文物：珍贵文化遗产的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "古代战争：中华民族历史上的挑战和荣耀",
                            time: "03-10"
                        },
                        {
                            listtitle: "古代编年史：历史的记录和传承之路",
                            time: "03-10"
                        },
                        {
                            listtitle: "夏商周：三千年前的历史记忆",
                            time: "06-10"
                        },
                        {
                            listtitle: "秦汉帝国：统一中华大地的历史巨人",
                            time: "05-16"
                        },
                        {
                            listtitle: "唐宋元明清：中国历史文化的显著时期",
                            time: "05-10"
                        },
                        {
                            listtitle: "中华民族：多元文化融合的民族群体",
                            time: "05-05"
                        },
                        {
                            listtitle: "四大发明：科技进步带动文化推广",
                            time: "04-11"
                        },
                        {
                            listtitle: "丝绸、茶叶、瓷器：华夏文化的代表物品",
                            time: "04-03"
                        },
                        {
                            listtitle: "长江、黄河、珠江：祖国母亲的三大江河",
                            time: "03-30"
                        },
                        {
                            listtitle: "资治通鉴：中国历史上的一部巨著",
                            time: "03-30"
                        },
                        {
                            listtitle: "东方红：中国历史上的人造卫星",
                            time: "03-30"
                        },
                        {
                            listtitle: "贸易通商：古代“一带一路”先河",
                            time: "03-30"
                        },
                        {
                            listtitle: "古代遗址：走进祖先的历史足迹",
                            time: "03-30"
                        },
                        {
                            listtitle: "清明上河图：描述古代都市生活的名画",
                            time: "03-30"
                        },
                        {
                            listtitle: "长城万里：中华民族的历史丰碑",
                            time: "03-30"
                        },
                        {
                            listtitle: "敦煌石窟：唐代壁画艺术的代表",
                            time: "03-30"
                        },
                        {
                            listtitle: "儒家文化：中国哲学思想的重要流派",
                            time: "03-30"
                        },
                        {
                            listtitle: "家谱文化：家族历史和文化的传承",
                            time: "03-30"
                        },
                        {
                            listtitle: "饮茶文化：社交与休闲文化的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "国宝级文物：珍贵文化遗产的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "古代战争：中华民族历史上的挑战和荣耀",
                            time: "03-10"
                        },
                        {
                            listtitle: "古代编年史：历史的记录和传承之路",
                            time: "03-10"
                        }, {
                            listtitle: "夏商周：三千年前的历史记忆",
                            time: "06-10"
                        },
                        {
                            listtitle: "秦汉帝国：统一中华大地的历史巨人",
                            time: "05-16"
                        },
                        {
                            listtitle: "唐宋元明清：中国历史文化的显著时期",
                            time: "05-10"
                        },
                        {
                            listtitle: "中华民族：多元文化融合的民族群体",
                            time: "05-05"
                        },
                        {
                            listtitle: "四大发明：科技进步带动文化推广",
                            time: "04-11"
                        },
                        {
                            listtitle: "丝绸、茶叶、瓷器：华夏文化的代表物品",
                            time: "04-03"
                        },
                        {
                            listtitle: "长江、黄河、珠江：祖国母亲的三大江河",
                            time: "03-30"
                        },
                        {
                            listtitle: "资治通鉴：中国历史上的一部巨著",
                            time: "03-30"
                        },
                        {
                            listtitle: "东方红：中国历史上的人造卫星",
                            time: "03-30"
                        },
                        {
                            listtitle: "贸易通商：古代“一带一路”先河",
                            time: "03-30"
                        },
                        {
                            listtitle: "古代遗址：走进祖先的历史足迹",
                            time: "03-30"
                        },
                        {
                            listtitle: "清明上河图：描述古代都市生活的名画",
                            time: "03-30"
                        },
                        {
                            listtitle: "长城万里：中华民族的历史丰碑",
                            time: "03-30"
                        },
                        {
                            listtitle: "敦煌石窟：唐代壁画艺术的代表",
                            time: "03-30"
                        },
                        {
                            listtitle: "儒家文化：中国哲学思想的重要流派",
                            time: "03-30"
                        },
                        {
                            listtitle: "家谱文化：家族历史和文化的传承",
                            time: "03-30"
                        },
                        {
                            listtitle: "饮茶文化：社交与休闲文化的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "国宝级文物：珍贵文化遗产的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "古代战争：中华民族历史上的挑战和荣耀",
                            time: "03-10"
                        },
                        {
                            listtitle: "古代编年史：历史的记录和传承之路",
                            time: "03-10"
                        }, {
                            listtitle: "夏商周：三千年前的历史记忆",
                            time: "06-10"
                        },
                        {
                            listtitle: "秦汉帝国：统一中华大地的历史巨人",
                            time: "05-16"
                        },
                        {
                            listtitle: "唐宋元明清：中国历史文化的显著时期",
                            time: "05-10"
                        },
                        {
                            listtitle: "中华民族：多元文化融合的民族群体",
                            time: "05-05"
                        },
                        {
                            listtitle: "四大发明：科技进步带动文化推广",
                            time: "04-11"
                        },
                        {
                            listtitle: "丝绸、茶叶、瓷器：华夏文化的代表物品",
                            time: "04-03"
                        },
                        {
                            listtitle: "长江、黄河、珠江：祖国母亲的三大江河",
                            time: "03-30"
                        },
                        {
                            listtitle: "资治通鉴：中国历史上的一部巨著",
                            time: "03-30"
                        },
                        {
                            listtitle: "东方红：中国历史上的人造卫星",
                            time: "03-30"
                        },
                        {
                            listtitle: "贸易通商：古代“一带一路”先河",
                            time: "03-30"
                        },
                        {
                            listtitle: "古代遗址：走进祖先的历史足迹",
                            time: "03-30"
                        },
                        {
                            listtitle: "清明上河图：描述古代都市生活的名画",
                            time: "03-30"
                        },
                        {
                            listtitle: "长城万里：中华民族的历史丰碑",
                            time: "03-30"
                        },
                        {
                            listtitle: "敦煌石窟：唐代壁画艺术的代表",
                            time: "03-30"
                        },
                        {
                            listtitle: "儒家文化：中国哲学思想的重要流派",
                            time: "03-30"
                        },
                        {
                            listtitle: "家谱文化：家族历史和文化的传承",
                            time: "03-30"
                        },
                        {
                            listtitle: "饮茶文化：社交与休闲文化的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "国宝级文物：珍贵文化遗产的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "古代战争：中华民族历史上的挑战和荣耀",
                            time: "03-10"
                        },
                        {
                            listtitle: "古代编年史：历史的记录和传承之路",
                            time: "03-10"
                        },
                    ],
                    recommand: [
                        {
                            listtitle: "清明上河图：描述古代都市生活的名画",
                            time: "03-30"
                        },
                        {
                            listtitle: "长城万里：中华民族的历史丰碑",
                            time: "03-30"
                        },
                        {
                            listtitle: "敦煌石窟：唐代壁画艺术的代表",
                            time: "03-30"
                        },
                        {
                            listtitle: "儒家文化：中国哲学思想的重要流派",
                            time: "03-30"
                        },
                        {
                            listtitle: "家谱文化：家族历史和文化的传承",
                            time: "03-30"
                        },
                        {
                            listtitle: "饮茶文化：社交与休闲文化的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "国宝级文物：珍贵文化遗产的代表",
                            time: "03-10"
                        },
                        {
                            listtitle: "古代战争：中华民族历史上的挑战和荣耀",
                            time: "03-10"
                        },
                        {
                            listtitle: "古代编年史：历史的记录和传承之路",
                            time: "03-10"
                        },
                    ],
                    hot: [
                        {
                            listtitle: "夏商周：三千年前的历史记忆",
                            time: "06-10"
                        },
                        {
                            listtitle: "秦汉帝国：统一中华大地的历史巨人",
                            time: "05-16"
                        },
                        {
                            listtitle: "唐宋元明清：中国历史文化的显著时期",
                            time: "05-10"
                        },
                        {
                            listtitle: "中华民族：多元文化融合的民族群体",
                            time: "05-05"
                        },
                        {
                            listtitle: "四大发明：科技进步带动文化推广",
                            time: "04-11"
                        },
                        {
                            listtitle: "丝绸、茶叶、瓷器：华夏文化的代表物品",
                            time: "04-03"
                        },
                        {
                            listtitle: "长江、黄河、珠江：祖国母亲的三大江河",
                            time: "03-30"
                        },
                        {
                            listtitle: "资治通鉴：中国历史上的一部巨著",
                            time: "03-30"
                        },
                        {
                            listtitle: "东方红：中国历史上的人造卫星",
                            time: "03-30"
                        },
                        {
                            listtitle: "贸易通商：古代“一带一路”先河",
                            time: "03-30"
                        },
                    ]
                }
            ],

        }
    }
}
</script>
<style scoped>
.main {
    height: 100%;
    width: 100%;
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

.body {
    padding: 25px;
    width: 89%;
    margin: 0 auto;
    display: flex;
    justify-content: space-between;
    padding: 5px;
    background-color: rgb(246, 246, 246);
}
</style>