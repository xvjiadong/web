<template>
    <div>
        <div class="header">
            <div class="topnav">
                <img class="leftnav" src="../../public/门户网站v1/LOGO.png">
                <div class="centernav">
                    <ul
                        style="display: flex;justify-content: space-between;width: 100%;padding: 0;list-style-type: none;">
                        <li class="liblock">首页</li>
                        <li class="liblock"><a href="#block2" style="color: white;text-decoration: none;">民用数据</a></li>
                        <li class="liblock"><a href="#block3" style="color: white;text-decoration: none;">服务优势</a></li>
                        <li class="liblock"><a href="#block4" style="color: white;text-decoration: none;">服务流程</a></li>
                        <li class="liblock"><a href="#block5" style="color: white;text-decoration: none;">平台简介</a></li>
                    </ul>
                </div>
                <div style="display: flex;justify-content: space-between;width: 16.5%;">
                    <button @click="gotologin" class="rightnav">登录</button>
                    <button @click="$router.push('/company_enter')" class="rightnav2">公司入驻办理</button>
                </div>
            </div>
        </div>
        <div id="block2" class="data_service">
            <h1>民用数据服务</h1>
            <div class="fontblock">
                <span @click="active = 0; line.right = '78%'" class="font"
                    :class="{ 'fontchoose': active == 0 }">图像标注</span>
                <span @click="active = 1; line.right = '39%'" class="font"
                    :class="{ 'fontchoose': active == 1 }">文本标注</span>
                <span @click="active = 2; line.right = '0'" class="font"
                    :class="{ 'fontchoose': active == 2 }">数据增强</span>
                <div :style="line"></div>
            </div>
            <el-carousel v-if="active == 0" @change="change" :interval="2000" type="card" height="200px"
                style="width: 60%;margin-top: 35px;">
                <el-carousel-item v-for="(item, index) in pic" :key="item.text">
                    <div
                        :style="`display:flex;flex-direction:column;justify-content:flex-end;align-items:flex-start;width:100%;height:100%;backgroundSize:100% 100%;backgroundRereat:no-repeat;backgroundImage:url(${item.url})`">
                        <div class="bg" :class="{ 'bg1': currentindex == index, }"
                            style="text-align: left;font-size: 25px;color: white;padding-left: 10px;padding-bottom: 10px;width: 100%;">
                            {{ item.text }}</div>
                    </div>
                </el-carousel-item>
            </el-carousel>
            <el-carousel v-if="active == 1" @change="change" :interval="2000" type="card" height="200px"
                style="width: 60%;margin-top: 35px;">
                <el-carousel-item v-for="(item, index) in text" :key="item.text">
                    <div
                        :style="`display:flex;flex-direction:column;justify-content:flex-end;align-items:flex-start;width:100%;height:100%;backgroundSize:100% 100%;backgroundRereat:no-repeat;backgroundImage:url(${item.url})`">
                        <div class="bg" :class="{ 'bg1': currentindex == index, }"
                            style="text-align: left;font-size: 25px;color: white;padding-left: 10px;padding-bottom: 10px;width: 100%;">
                            {{ item.text }}</div>
                    </div>
                </el-carousel-item>
            </el-carousel>
        </div>
        <div id="block3" class="service">
            <div style="padding-top: 35px;">
                <h1 style="color: white;margin-bottom: 25px;margin-top: 0;">服务优势</h1>
            </div>
            <div style="width: 75%;height: 80%;display: flex;justify-content: space-between">
                <div
                    style="width: 24%;height: 80%;background-color: white;border-radius: 12px ;text-align: left;padding: 15px;">
                    <img style="width: 200px;height: 150px;" src="../../public/门户网站v1/icon/运维icon.png">
                    <h2 style="margin-top: 0;padding-left: 15px;">运维体系完善</h2>
                    <span style="font-size: 20px;color: rgb(121, 121, 121);letter-spacing: 4px;">
                        10年业务运维经验，已建立标准
                        化操作流程，商务对接--内部
                        评估--人员培训--专项考核--
                        架构组建技术保障--试采试标
                        --质检机制--风险预警--确认
                        交付。
                    </span>
                </div>
                <div
                    style="width: 70%;height: 85%;display: flex;flex-direction: column;justify-content: space-between;">
                    <div style="width: 100%;height: 48%;display: flex;justify-content: space-between;">
                        <div style="width: 48%;background-color: white;height: 100%;border-radius: 15px;">
                            <div
                                style="display: flex;justify-content: flex-start;align-items: center;height: 20%;padding: 20px;">
                                <img style="width: 50px;height: 50px;" src="../../public/门户网站v1/icon/资源icon.png">
                                <h2 style="margin-top: 0;margin-bottom: 0;padding-left: 15px;">运维体系完善</h2>
                            </div>
                            <div
                                style="padding: 10px;font-size: 16px;color: rgb(121, 121, 121);letter-spacing: 4px;text-align: left;margin-top: 5px;">
                                10年业务运维经验，已建立标准化操作流程
                                商务对接--内部评估--人员培训--专项考核
                                --架构组建技术保障--试采试标--质检机制
                                --风险预警--确认交付。
                            </div>
                        </div>
                        <div style="width: 48%;background-color: white;height: 100%;border-radius: 15px;">
                            <div
                                style="display: flex;justify-content: flex-start;align-items: center;height: 20%;padding: 20px;">
                                <img style="width: 50px;height: 50px;" src="../../public/门户网站v1/icon/研发icon.png">
                                <h2 style="margin-top: 0;margin-bottom: 0;padding-left: 15px;">注重平台研发</h2>
                            </div>
                            <div
                                style="padding: 10px;font-size: 16px;color: rgb(121, 121, 121);letter-spacing: 4px;text-align: left;margin-top: 5px;">
                                标注平台拥有实时量化的可视化管理系统，集
                                数据管理、项目管理、人员管理等功能为一体
                                可实现半自动辅助标注、AI算法预处理自动质
                                检等功能。
                            </div>
                        </div>
                    </div>
                    <div style="width: 100%;height: 48%;display: flex;justify-content: space-between;">
                        <div style="width: 48%;background-color: white;height: 100%;border-radius: 15px;">
                            <div
                                style="display: flex;justify-content: flex-start;align-items: center;height: 20%;padding: 20px;">
                                <img style="width: 50px;height: 50px;" src="../../public/门户网站v1/icon/数据安全icon.png">
                                <h2 style="margin-top: 0;margin-bottom: 0;padding-left: 15px;">数据安全合规</h2>
                            </div>
                            <div
                                style="padding: 10px;font-size: 16px;color: rgb(121, 121, 121);letter-spacing: 4px;text-align: left;margin-top: 5px;">
                                通过IS09001ISO27001体系认证，数据上链
                                人证协议合拍;签署用户授权书、项目保护议、
                                用户须知;团队全员学习GDPR，EAR，信安标
                                委。
                            </div>
                        </div>
                        <div style="width: 48%;background-color: white;height: 100%;border-radius: 15px;">
                            <div
                                style="display: flex;justify-content: flex-start;align-items: center;height: 20%;padding: 20px;">
                                <img style="width: 50px;height: 50px;" src="../../public/门户网站v1/icon/稳定安全icon.png">
                                <h2 style="margin-top: 0;margin-bottom: 0;padding-left: 15px;">团队安全稳定</h2>
                            </div>
                            <div
                                style="padding: 10px;font-size: 16px;color: rgb(121, 121, 121);letter-spacing: 4px;text-align: left;margin-top: 5px;">
                                10年业务运维经验，已建立标准化操作流程
                                商务对接--内部评估--人员培训--专项考核
                                --架构组建技术保障-试采试标--质检机制
                                --风险预警--确认交付。
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div id="block4" class="procedure">
            <h1>服务流程</h1>
            <img src="../../public/门户网站v1/流程图.jpg">
        </div>
        <div id="block5" class="introduce">
            <div style="display: flex;width: 70%;justify-content: space-between;align-items: center;">
                <img style="width: 350px;height: 350px;" src="../../public/门户网站v1/平台简介.jpg">
                <div style="width: 50%;text-align: left;">
                    <h1 style="text-align: left;">平台简介</h1>
                    <span style="font-size: 16px;color: rgb(121, 121, 121);letter-spacing: 4px;">
                        我们的数据标注平台是一款功能强大、多样化的工具，专为企业和项目管理者以及数据标注员设计。平台支持多种标注类型，包括分割标注、物体检测、图片分类、OCR标注、点标注、线标注、信息抽取标注、文本分类、抽取式阅读理解、文本摘要等等。无论您需要何种类型的数据标注，我们都能满足您的需求。

                        不仅如此，我们的平台还支持多种标注方式，包括自动标注、半自动标注等，从而提高标注效率，节省时间成本。在我们的平台上，企业管理员拥有最高权限，负责处理公司事务、管理权限、制定规范；项目管理员则是核心业务发起人，负责创建项目、分发任务；而数据标注员是核心业务承办者，负责接收任务、标注数据。

                        无论您是需要数据标注的企业管理者还是项目管理者，或是数据标注员，我们的平台都能为您提供最优质的服务，帮助您高效完成数据标注任务，推动项目顺利进行。
                    </span>
                </div>
            </div>

        </div>
        <div id="block6" class="footer">
            <div
                style="height: 80px;width: 70%;;margin-top: 35px;display: flex;justify-content: space-between;align-items: flex-end;">
                <img src="../../public/门户网站v1/LOGO.png">
                <ul
                    style="display: flex;justify-content: space-between;width: 50%;padding: 0;list-style-type: none;color: white;">
                    <li class="liblock">首页</li>
                    <li class="liblock">民用数据</li>
                    <li class="liblock">服务优势</li>
                    <li class="liblock">服务流程</li>
                    <li class="liblock">公司简介</li>
                </ul>
            </div>
            <el-divider></el-divider>
            <div style="height: 80px;width: 70%;display: flex;justify-content: space-between;align-items: flex-start;">
                <span style="color: rgb(167,172,175);font-size: 20px;">鼠标数据标注平台版权所有</span>
                <div style="display: flex;">
                    <span style="color: rgb(167,172,175);font-size: 20px;cursor: pointer;">法律声明|</span>
                    <span style="color: rgb(167,172,175);font-size: 20px;cursor: pointer;">使用协议|</span>
                    <span style="color: rgb(167,172,175);font-size: 20px;cursor: pointer;">友情链接</span>
                </div>
            </div>
        </div>
    </div>

</template>
<script>
export default {
    data() {
        return {
            active: 0,
            line: {
                position: 'absolute',
                bottom: '0',
                right: "78%",
                width: '100px',
                height: '3px',
                backgroundColor: 'rgb(47, 142, 255)',
                transition: 'all 0.2s'
            },
            pic: [
                {
                    url: "../../门户网站v1/点标注.jpg",
                    text: "点标注"
                },
                {
                    url: "../../门户网站v1/线标注.jpg",
                    text: "线标注"
                },
                {
                    url: "../../门户网站v1/ocr标注.jpg",
                    text: "ocr标注"
                },
                {
                    url: "../../门户网站v1/图片分类标注.jpg",
                    text: "图片分类标注"
                },
                {
                    url: "../../门户网站v1/物体检测.jpg",
                    text: "物体检测"
                },
                {
                    url: "../../门户网站v1/分割标注.jpg",
                    text: "分割标注"
                }
            ],
            text: [
                {
                    url: "../../门户网站v1/信息抽取标注.webp.jpg",
                    text: "信息抽取标注"
                },
                {
                    url: "../../门户网站v1/文本分类.png",
                    text: "文本分类"
                },
                {
                    url: "../../门户网站v1/文本摘要.jpg",
                    text: "文本摘要标注"
                },
                {
                    url: "../../门户网站v1/抽取式阅读理解.jpg",
                    text: "阅读理解"
                },
            ],
            currentindex: 0
        }
    },
    methods: {
        gotologin() {
            this.$router.push("/login")
        },
        change(newvalue) {
            this.currentindex = newvalue
        }
    },

}
</script>
<style scoped>
.header {
    background-image: url('../../public/门户网站v1/banner改.png');
    background-repeat: no-repeat;
    background-size: 100% 100%;
    width: 100%;
    height: 700px;
    display: flex;
    flex-direction: column;
    justify-content: flex-start;
    align-items: center;
}

.topnav {
    width: 85%;
    height: 100px;
    display: flex;
    justify-content: space-around;
    align-items: center;
}

.leftnav {
    width: 100px;
    height: 80px;
}

.centernav {
    color: white;
    width: 40%;
    height: 100%;
    display: flex;
    align-items: center;
}

.liblock {
    text-decoration: none;
    font-size: 18px;
    cursor: pointer;
}

.liblock:hover {
    font-weight: 600;
}

.rightnav {
    cursor: pointer;
    background-color: rgb(47, 142, 255);
    border-radius: 10px;
    color: white;
    font-size: 15px;
    width: 80px;
    height: 35px;
    padding: 5px;
    border: 0px;
}

.rightnav2 {
    cursor: pointer;
    background-color: rgb(47, 142, 255);
    border-radius: 10px;
    color: white;
    font-size: 15px;
    width: 120px;
    height: 35px;
    padding: 5px;
    border: 0px;
}

.data_service {
    height: 450px;
    padding-top: 35px;
    display: flex;
    flex-direction: column;
    align-items: center;
}

.fontblock {
    margin-top: 30px;
    width: 30%;
    display: flex;
    justify-content: space-between;
    height: 60px;
    position: relative;
}

.font {
    cursor: pointer;
    font-size: 25px;

}

.fontchoose {
    color: rgb(47, 142, 255);
}

.bg {
    background-color: rgba(120, 120, 121, 0.5);
    border-radius: 10px 15px 15px 0px;
}

.bg1 {
    background-color: rgba(48, 102, 167, 0.4);
    border-radius: 10px 15px 15px 0px;
}

.service {
    width: 100%;
    height: 710px;
    background-image: url('../../public/门户网站v1/服务优势背景.png');
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
}

.procedure {
    width: 100%;
    height: 710px;
}

.introduce {
    width: 100%;
    height: 550px;
    display: flex;
    justify-content: center;
}

.footer {
    width: 100%;
    height: 250px;
    background-color: rgb(35, 47, 56);
    display: flex;
    flex-direction: column;
    align-items: center;
}

/deep/.el-divider--horizontal {
    background-color: rgb(48, 59, 68);
    display: block;
    height: 1px;
    width: 70%;
    margin: 24px 0;
}
</style>