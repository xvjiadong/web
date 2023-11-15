<template>
    <div style="width: 95%;">
        <div class="step">
            <div style="width: 60%;">
                <el-steps :active="active" finish-status="success" align-center process-status="finish" space="100%">
                    <el-step title="填写基本信息" icon="el-icon-edit"></el-step>
                    <el-step title="选择团队成员" icon="el-icon-upload"></el-step>
                </el-steps>
            </div>
        </div>
        <el-card class="box-card" v-if="active == 0">
            <div slot="header" class="cardheader">
                <span>基本信息</span>
            </div>
            <el-form ref="form1" :model="task" :rules="taskrule" label-width="100px" class="form" label-position="left">
                <el-form-item prop="taskname" label="任务名称:" class="formitem">
                    <el-input style="width: 60%;" size="mini" v-model="task.taskname" placeholder="限制50个字符以内,支持汉字、大小写英文、数字"
                        maxlength="50" show-word-limit></el-input>
                </el-form-item>
                <el-form-item prop="projectid" label="选择数据集:" class="formitem">
                    <el-select filterable="" v-model="task.projectid" size="mini" style="width: 25%;">
                        <el-option v-for="item in projectlist" :key="item.projectid" :value="item.projectid"
                            :label="item.label">
                        </el-option>
                    </el-select>
                    <el-select filterable v-model="task.projectversion" size="mini" :disabled="task.projectid === ''"
                        style="width: 22%;margin-left: 8px;">
                        <el-option v-for="item in versionlist" :key="item.versionid" :value="item.versionname"
                            :label="`${item.versionname}-${item.marktype}`">
                        </el-option>
                    </el-select>
                    <span style="font-size: 12px; color: rgb(36,104,242);cursor: pointer;margin-left: 8px;"
                        @click="jump('/CreateProject')">创建项目</span>
                </el-form-item>
                <el-form-item label="标注任务样例" prop="modelfile">
                    <el-upload ref="upload" accept=".pdf" action="" :file-list="task.modelfile" :limit="1"
                        v-model="task.modelfile" draggable style="text-align: left;" :auto-upload="false"
                        :on-change="uploadchange" :on-remove="uploadremove">
                        <el-button size="mini" style="border: 1px solid rgb(36,104,242);color: rgb(36,104,242);">
                            <i class="el-icon-upload"></i>点击上传</el-button>
                        <span slot="tip" class="el-upload__tip" style="margin-left: 8px;">(支持20M以内的pdf文件)</span>
                    </el-upload>
                </el-form-item>
                <el-form-item label="设置标签" prop="selectlabel" v-if="task.projectversion !== ''">
                    <el-card style="width: 37%;">
                        <div slot="header">
                            <div v-if="!addlabelvisible && !addlabelgroupvisible"
                                style="display: flex;justify-content: space-between;">
                                <span>标签数量({{ task.selectlabel.length }}/1000)</span>
                                <div>
                                    <el-button style="background-color: rgb(36,104,242);font-size: 12px;color: white;"
                                        size="mini" @click="addlabelvisible = true">
                                        <i class="el-icon-price-tag"></i>
                                        添加标签
                                    </el-button>
                                    <el-button style="background-color: rgb(36,104,242);font-size: 12px;color: white;"
                                        size="mini" @click="addlabelgroupvisible = true">
                                        <i class="el-icon-guide"></i>
                                        添加标签组
                                    </el-button>
                                </div>
                            </div>
                            <div v-if="addlabelvisible"
                                style="display: flex;flex-direction: column;align-items: left;justify-content:flex-start;">
                                <div style="display: flex;justify-content: left;align-items: center;">
                                    <input class="input" size="mini" v-model="labelvalue" placeholder="请输入标签名称，不支持重复标签">
                                    <i class="el-icon-check labelicon" @click="surelabelinput"></i>
                                    <i class="el-icon-close labelicon" @click="closelabelinput"></i>
                                </div>
                                <span v-if="emptylabel" id="repeattext" class="animate__animated animate__shakeX">
                                    {{ labelerror }}
                                </span>
                                <span v-else class="suretext" :class="{ addok: labelsure !== '待添加' }">
                                    {{ labelsure }}
                                </span>
                            </div>
                            <div v-if="addlabelgroupvisible"
                                style="display: flex;flex-direction: column;align-items: left;justify-content:flex-start;">
                                <div style="display: flex;justify-content: left;align-items: center;">
                                    <select v-model="selectlabelgroup" class="input">
                                        <option v-for="item in labelgroup" :key="item" :value="item" :label="item">
                                        </option>
                                    </select>
                                    <i class="el-icon-check labelicon" @click="surelabelgroupselect"></i>
                                    <i class="el-icon-close labelicon" @click="closelabelgroupselect"></i>
                                </div>
                                <span v-if="emptylabel" id="repeattext" class="animate__animated animate__shakeX">
                                    {{ labelerror }}
                                </span>
                                <span v-else class="suretext" :class="{ addok: labelsure !== '待添加' }">
                                    {{ labelsure }}
                                </span>
                            </div>
                        </div>
                        <div style="display: flex;justify-content: left;">
                            <span>序号</span>
                            <span style="margin-left: 15px;">标签名</span>
                        </div>
                        <div style="height: 160px;overflow-y: scroll;">
                            <div v-for="(item, index) in task.selectlabel" :key="index"
                                style="display: flex;justify-content: left;">
                                <div>
                                    {{ index + 1 }}
                                </div>
                                <div v-if="!setlabel.includes(index + 1)"
                                    style="margin-left: 25px;display: flex;justify-content: left;align-items: center;">
                                    <div class="labelblock" :id="`labeldiv${index + 1}`">{{ item }}</div>
                                    <el-tooltip content="编辑标签" placement="top-start">
                                        <i class="el-icon-edit labelicon" @click="editlabel(index + 1)"></i>
                                    </el-tooltip>
                                    <el-tooltip content="删除标签" placement="top-end">
                                        <i class="el-icon-delete labelicon" @click="deletelabel(index + 1)"></i>
                                    </el-tooltip>

                                </div>
                                <div v-else
                                    style="margin-left: 25px;display: flex;justify-content: left;align-items: center;">
                                    <input :value="task.selectlabel[index]" class="inputlabel"
                                        :id="`labelinput${index + 1}`">
                                    <el-tooltip content="保存编辑" placement="top-start">
                                        <i class="el-icon-check labelicon" @click="editsure(index + 1)"></i>
                                    </el-tooltip>
                                    <el-tooltip content="取消编辑" placement="top-end">
                                        <i class="el-icon-close labelicon" @click="canceledit(index + 1)"></i>
                                    </el-tooltip>
                                </div>
                            </div>
                        </div>
                    </el-card>
                </el-form-item>
                <el-form-item class="formitem">
                    <el-button size="small" type="primary" @click="complete1">前往创建团队</el-button>
                    <el-button size="small" @click="jump('/TaskList')">取消</el-button>
                </el-form-item>
            </el-form>
        </el-card>
        <el-card class="box-card" v-if="active == 1">
            <div slot="header" class="cardheader">
                <el-page-header @back="goBack" content="人员选择">
                </el-page-header>
            </div>
            <el-form ref="form2" :model="task" :rules="taskrule2" label-width="110px" class="form" label-position="left">
                <el-form-item label="团队成员" prop="taskperson" class="formitem">
                    <el-select :disabled="true" filterable size="mini" multiple v-model="task.taskperson" style="width:60%"
                        placeholder="请选择团队成员">
                        <el-option v-for="item in members " :key="item.labelerid" :value="item.labelerid"
                            style="margin-top:5px;height:40px">
                            <div slot style="display: flex;justify-content: left;align-items:center;">
                                <el-avatar icon="el-icon-user-solid"></el-avatar>
                                <div style="display:flex;flex-direction:column;justify-content:center;margin-left:5px">
                                    <span style="font: 0.8em sans-serif;">{{ item.labelername }}</span>
                                    <span style="font: 0.8em sans-serif;">正在执行{{ item.nownumber }}个任务</span>
                                </div>
                            </div>
                        </el-option>
                    </el-select>
                    <el-input suffix-icon="el-icon-search" placeholder="请输入数据标注员id或用户名" size="mini" v-model="memberfilter"
                        style="width:28%;margin-left:10px"></el-input>
                    <el-tooltip content="查看全部标注员，请将计数器调至-1" placement="top-start">
                        <el-input size="mini" style="width: 10%;" v-model="accpettasknumber" type="number"
                            :min="-1"></el-input>
                    </el-tooltip>
                    <el-empty v-if="showmember.length === 0" description="所有人都执行着更多的任务"
                        style="height:200px;padding:0px;"></el-empty>
                    <el-checkbox-group v-else v-model="task.taskperson" :min="0" :max="10"
                        style="width:100%;height:200px;overflow-y: scroll;">
                        <el-checkbox v-for="item in showmember" :label="item.labelerid" :key="item.labelerid">
                            <div style="display: flex;justify-content: left;align-items:center;">
                                <el-avatar :src="item.avatar"></el-avatar>
                                <div style="display:flex;flex-direction:column;justify-content:center;">
                                    <span style="font: 0.8em sans-serif;">{{ item.labelername }}</span>
                                    <span style="font: 0.8em sans-serif;">正在执行{{ item.nownumber }}个任务</span>
                                </div>
                            </div>
                        </el-checkbox>
                    </el-checkbox-group>
                </el-form-item>
                <el-form-item prop="deadline" label="截止时间" class="formitem">
                    <el-date-picker size="mini" v-model="task.deadline" type="datetime" placeholder="请选择日期时间"
                        :time-arrow-control="true">
                    </el-date-picker>
                </el-form-item>
                <el-form-item class="formitem">
                    <el-button size="mini" @click="complete2">导入数据集</el-button>
                    <el-button size="mini" @click="jump('/TaskList')">取消</el-button>
                </el-form-item>
            </el-form>
        </el-card>
    </div>
</template>
<script>
export default {
    name: "TaskSchedule",
    components: {

    },
    data() {
        let validatetaskname = (rule, value, callback) => {
            if (value === "") {
                return callback(new Error('名称不能为空'));
            } else if (!/^[\u4e00-\u9fa5a-zA-Z0-9][\u4e00-\u9fa5a-zA-Z0-9_]{0,49}$/.test(value)) {
                return callback(new Error('项目名称仅支持中文、英文、数字'));
            } else {
                callback()
            }
        };
        let validateprojectid = (rule, value, callback) => {
            if (value === '' || this.task.projectversion === "") {
                return callback(new Error('请选择任务数据集'));
            } else {
                callback()
            }
        };
        let validatemodefile = (rule, value, callback) => {
            if (value.raw.size / 1024 / 1024 > 20) {
                return callback(new Error('标注样例文件大小不能超过20MB'));
            } else if (value.raw.name.split(".")[value.raw.name.split(".").length - 1] !== "pdf") {
                return callback(new Error('文件格式不符合'));
            } else {
                callback()
            }
        };
        let validatetaskperson = (rule, value, callback) => {
            if (value.length === 0) {
                return callback(new Error('请选择至少一位团队成员'));
            } else if (value.length > 15) {
                return callback(new Error('团队成员数量不能超过10个'));
            } else {
                callback()
            }
        };
        let validatedeadline = (rule, value, callback) => {
            if (value === "") {
                return callback(new Error('请选择任务截止日期'));
            } else {
                callback()
            }
        };
        let validateselectlabel = (rule, value, callback) => {
            if (value.length === 0) {
                return callback(new Error('请选择至少一条标签'));
            } else if (value.length > 1000) {
                return callback(new Error('标签数量不能超过1000个'));
            } else {
                callback()
            }
        };
        return {
            active: 0,
            task: {
                taskname: "",
                projectid: "",
                projectversion: "",
                taskperson: [],
                deadline: "",
                modelfile: [],
                selectlabel: ["11", "22", "33", "55", "565", "regfd", "46456"]
            },
            taskrule: {
                taskname: [
                    { required: true, validator: validatetaskname, trigger: 'blur' }
                ],
                projectid: [
                    { required: true, validator: validateprojectid, trigger: 'blur' }
                ],
                modefile: [
                    { validator: validatemodefile, trigger: 'blur' }
                ],
                selectlabel: [{ required: true, validator: validateselectlabel, trigger: 'blur' }]
            },
            taskrule2: {
                taskperson: [
                    { required: true, validator: validatetaskperson, trigger: 'blur' }
                ],
                deadline: [
                    { required: true, validator: validatedeadline, trigger: 'blur' }
                ],
            },
            projectlist: [
                {
                    projectid: "188865667",     //项目id
                    name: "测试数据1",          //项目名
                    datatype: "图像",          //数据类型
                    version: [                 //下辖版本
                        {
                            versionid: "1697286",      //版本id
                            versionname: "v1",         //版本号
                            versionnumber: "600",      //数据量
                            marktype: "图片分类",      //标注任务类型
                            markprocess: "0%",        //标注进度
                            children: [               //任务
                                {
                                    taskid: "1",       //任务id
                                    taskname: "4848",
                                    tasknumber: "150",   //任务标注数量
                                    taskperson: "测试标注员1",   //任务承担人
                                    taskprocess: "15%",  //任务进度
                                    taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                    taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                    juideprocess: "0%",     //审核进度
                                },
                                {
                                    taskid: "2",       //任务id
                                    taskname: "4848",
                                    tasknumber: "150",   //任务标注数量
                                    taskperson: "测试标注员2",   //任务承担人
                                    taskprocess: "12%",  //任务进度
                                    taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                    taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                    juideprocess: "0%",     //审核进度
                                },
                                {
                                    taskid: "3",       //任务id
                                    taskname: "4848",
                                    tasknumber: "150",   //任务标注数量
                                    taskperson: "测试标注员3",   //任务承担人
                                    taskprocess: "42%",  //任务进度
                                    taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                    taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                    juideprocess: "0%",     //审核进度
                                },
                                {
                                    taskid: "4",       //任务id
                                    taskname: "4848",
                                    tasknumber: "150",   //任务标注数量
                                    taskperson: "测试标注员4",   //任务承担人
                                    taskprocess: "56%",  //任务进度
                                    taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                    taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                    juideprocess: "0%",     //审核进度
                                }
                            ]
                        },
                        {
                            versionid: "1592156",
                            versionname: "v2",
                            versionnumber: "452",
                            datatype: "图像",
                            marktype: "图像文本识别",
                            markprocess: "15%",

                        },
                        {
                            versionid: "1578156",
                            versionname: "v3",
                            versionnumber: "452",
                            datatype: "图像",
                            marktype: "图像文本识别",
                            markprocess: "15%",

                        },
                        {
                            versionid: "158756",
                            versionname: "v4",
                            versionnumber: "452",
                            datatype: "图像",
                            marktype: "图像文本识别",
                            markprocess: "15%",

                        }
                    ]
                },
                {
                    projectid: "595398126",
                    name: "测试数据2",
                    datatype: "文本",
                    version: [
                        {
                            versionid: "7952926",
                            versionname: "v1",
                            versionnumber: "456",

                            marktype: "文本分类",
                            markprocess: "15%",

                        },
                        {
                            versionid: "2375895",
                            versionname: "v2",
                            versionnumber: "324",
                            datatype: "文本",
                            marktype: "信息抽取标注",
                            markprocess: "78%",

                        }
                    ]
                },
                {
                    projectid: "1",
                    name: "测试数据2",
                    datatype: "文本",
                    version: [
                        {
                            versionid: "7952926",
                            versionname: "v1",
                            versionnumber: "456",

                            marktype: "文本分类",
                            markprocess: "15%",

                        },
                        {
                            versionid: "2375895",
                            versionname: "v2",
                            versionnumber: "324",
                            datatype: "文本",
                            marktype: "信息抽取标注",
                            markprocess: "78%",

                        }
                    ]
                },
                {
                    projectid: "2",
                    name: "测试数据2",
                    datatype: "文本",
                    version: [
                        {
                            versionid: "7952926",
                            versionname: "v1",
                            versionnumber: "456",

                            marktype: "文本分类",
                            markprocess: "15%",

                        },
                        {
                            versionid: "2375895",
                            versionname: "v2",
                            versionnumber: "324",
                            datatype: "文本",
                            marktype: "信息抽取标注",
                            markprocess: "78%",

                        }
                    ]
                },
                {
                    projectid: "3",
                    name: "测试数据2",
                    datatype: "文本",
                    version: [
                        {
                            versionid: "7952926",
                            versionname: "v1",
                            versionnumber: "456",

                            marktype: "文本分类",
                            markprocess: "15%",

                        },
                        {
                            versionid: "2375895",
                            versionname: "v2",
                            versionnumber: "324",
                            datatype: "文本",
                            marktype: "信息抽取标注",
                            markprocess: "78%",

                        }
                    ]
                },
                {
                    projectid: "4",
                    name: "测试数据2",
                    datatype: "文本",
                    version: [
                        {
                            versionid: "7952926",
                            versionname: "v1",
                            versionnumber: "456",

                            marktype: "文本分类",
                            markprocess: "15%",

                        },
                        {
                            versionid: "2375895",
                            versionname: "v2",
                            versionnumber: "324",
                            datatype: "文本",
                            marktype: "信息抽取标注",
                            markprocess: "78%",

                        }
                    ]
                },
            ],
            labelvalue: "",
            addlabelvisible: false,
            addlabelgroupvisible: false,
            emptylabel: false,
            labelerror: "",
            labelsure: "待添加",
            labelgroup: ["mouseone", "mousetwo", "mousethree", "mousefour", "mousefive"],
            mouseone: ["大赛", "11", "22", "13", "23"],
            mousetwo: ["大sad", "62", "484", "93", "483"],
            mousethree: ["大瓦尔塔", "11规范", "22规范", "13阿萨德", "2453"],
            mousefour: ["大赛、突然覆盖", "11覆盖", "规范福贵22", "规划13", "23"],
            mousefive: ["11", "22", "33", "55", "565", "regfd", "46456", "11", "22", "33", "55", "565", "regfd", "46456"],
            selectlabelgroup: "",
            inputvalue: "",
            setlabel: [],
            members: [
                {
                    labelerid: "1",
                    labelername: "鼠大",
                    nownumber: 4,
                    avatar: "http://120.55.63.197:3000/images/33.jpg"
                },
                {
                    labelerid: "2",
                    labelername: "鼠二",
                    nownumber: 56,
                    avatar: ""
                },
                {
                    labelerid: "3",
                    labelername: "鼠三",
                    nownumber: 10,
                    avatar: ""
                },
                {
                    labelerid: "4",
                    labelername: "鼠四",
                    nownumber: 28,
                    avatar: ""
                },
                {
                    labelerid: "5",
                    labelername: "鼠五",
                    nownumber: 25,
                    avatar: ""
                },
                {
                    labelerid: "6",
                    labelername: "鼠大",
                    nownumber: 4,
                    avatar: "http://120.55.63.197:3000/images/33.jpg"
                },
                {
                    labelerid: "7",
                    labelername: "鼠二",
                    nownumber: 56,
                    avatar: ""
                },
                {
                    labelerid: "8",
                    labelername: "鼠三",
                    nownumber: 10,
                    avatar: ""
                },
                {
                    labelerid: "9",
                    labelername: "鼠四",
                    nownumber: 28,
                    avatar: ""
                },
                {
                    labelerid: "10",
                    labelername: "鼠五",
                    nownumber: 25,
                    avatar: ""
                },
                {
                    labelerid: "11",
                    labelername: "鼠大",
                    nownumber: 4,
                    avatar: "http://120.55.63.197:3000/images/33.jpg"
                },
                {
                    labelerid: "12",
                    labelername: "鼠二",
                    nownumber: 56,
                    avatar: ""
                },
                {
                    labelerid: "13",
                    labelername: "鼠三",
                    nownumber: 10,
                    avatar: ""
                },
                {
                    labelerid: "14",
                    labelername: "鼠四",
                    nownumber: 28,
                    avatar: ""
                },
                {
                    labelerid: "15",
                    labelername: "鼠五",
                    nownumber: 25,
                    avatar: ""
                },
                {
                    labelerid: "16",
                    labelername: "鼠大",
                    nownumber: 4,
                    avatar: "http://120.55.63.197:3000/images/33.jpg"
                },
                {
                    labelerid: "17",
                    labelername: "鼠二",
                    nownumber: 56,
                    avatar: ""
                },
                {
                    labelerid: "18",
                    labelername: "鼠三",
                    nownumber: 10,
                    avatar: ""
                },
                {
                    labelerid: "19",
                    labelername: "鼠四",
                    nownumber: 28,
                    avatar: ""
                },
                {
                    labelerid: "20",
                    labelername: "鼠五",
                    nownumber: 25,
                    avatar: ""
                },
            ],
            memberfilter: "",
            accpettasknumber: -1
        }
    },
    computed: {
        versionlist() {
            if (this.task.projectid) {
                return this.projectlist.filter(item => {
                    return item.projectid == this.task.projectid
                })[0].version
            }
            return []
        },
        showmember() {
            return this.members.filter(item => {
                return (item.labelerid.includes(this.memberfilter) || item.labelername.includes(this.memberfilter)) && (item.nownumber <= this.accpettasknumber || this.accpettasknumber == -1)
            })
        }
    },
    methods: {
        editlabel(id) {
            this.setlabel.push(id)
            this.$nextTick(() => {
                document.getElementById("labelinput" + id).focus()
            })
        },
        editsure(id) {
            if (document.getElementById("labelinput" + id).value === "") {
                document.getElementById("labelinput" + id).value = "标签名称不能为空"
                document.getElementById("labelinput" + id).classList.add("repeatlabel")
                setTimeout(() => {
                    document.getElementById("labelinput" + id).classList.remove("repeatlabel")
                    document.getElementById("labelinput" + id).value = this.task.selectlabel[id - 1]
                }, 800);
            } else if (!this.task.selectlabel.includes(document.getElementById("labelinput" + id).value) || this.task.selectlabel[id - 1] === document.getElementById("labelinput" + id).value) {
                this.task.selectlabel[id - 1] = document.getElementById("labelinput" + id).value
                this.setlabel = this.setlabel.filter((item) => {
                    return item !== id
                })
            } else {
                document.getElementById("labelinput" + id).value = "标签名称重复"
                document.getElementById("labelinput" + id).classList.add("repeatlabel")
                setTimeout(() => {
                    document.getElementById("labelinput" + id).classList.remove("repeatlabel")
                    document.getElementById("labelinput" + id).value = this.task.selectlabel[id - 1]
                }, 800);
            }
        },
        deletelabel(id) {
            this.task.selectlabel.splice(id - 1, 1)
        },
        canceledit(id) {
            this.setlabel = this.setlabel.filter((item) => {
                return item !== id
            })
        },
        complete1() {
            this.$refs.form1.validate((result) => {
                if (result) {
                    this.active += 1
                }
            })
        },
        complete2() {
            this.$refs.form2.validate((result) => {
                if (result) {
                    this.task.crectetime=this.timeturn(Date.now())
                    this.task.deadline = this.timeturn(this.task.deadline)
                    console.log(this.task);
                }
            })
        },
        uploadchange(file) {
            console.log(file);
            if (file.raw.size / 1024 / 1024 > 20) {
                this.$message({ type: "warning", message: file.name + "大小超过20MB" })
                this.$refs.upload.onRemove(file)
                return
            } else if (file.name.split(".")[file.name.split(".").length - 1] !== "pdf") {
                this.$message({ type: "warning", message: file.name + "文件格式不正确，请上传pdf文件" })
                this.$refs.upload.onRemove(file)
                return
            }
            this.task.modelfile.push(file)
        },
        uploadremove(file) {
            console.log(file);
            this.task.modelfile = []
        },
        jump(item) {
            this.$router.push(item)
        },
        surelabelinput() {
            if (this.labelvalue && !this.task.selectlabel.includes(this.labelvalue)) {
                this.task.selectlabel.push(this.labelvalue)
                this.labelvalue = ""
                this.labelsure = "添加成功"
                this.emptylabel = false
                return
            } else if (this.labelvalue === "") {
                this.labelerror = "标签名称不能为空"
                this.emptylabel = true
            } else {
                this.labelerror = "标签名称重复"
                this.emptylabel = true
            }
        },
        closelabelinput() {
            this.labelvalue = ""
            this.emptylabel = false
            this.addlabelvisible = false
        },
        surelabelgroupselect() {
            if (this.selectlabelgroup === "") {
                this.labelerror = "请选择标签组"
                this.emptylabel = true
            } else {
                let a = []
                this[this.selectlabelgroup].map((item) => {
                    if (this.task.selectlabel.includes(item)) {
                        a.push(item)
                    } else {
                        this.task.selectlabel.push(item)
                    }
                })
                if (a.length > 0) {
                    this.labelerror = "以下标签名称重复："
                    a.forEach(item => {
                        this.labelerror += item + "  "
                    })
                    this.emptylabel = true
                } else {
                    this.labelsure = "添加成功"
                    this.emptylabel = false
                }
            }
        },
        closelabelgroupselect() {
            this.selectlabelgroup = ""
            this.addlabelgroupvisible = false
            this.emptylabel = false
        },
        goBack() {
            this.active -= 1
        },
        timeturn(item) {
            const date = new Date(item)
            const year = date.getFullYear();
            const month = String(date.getMonth() + 1).padStart(2, '0');
            const day = String(date.getDate()).padStart(2, '0');
            const hours = String(date.getHours()).padStart(2, '0');
            const minutes = String(date.getMinutes()).padStart(2, '0');
            const seconds = String(date.getSeconds()).padStart(2, '0');
            const formattedDateString = `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
            return formattedDateString
        }
    },
    mounted() {
        console.log(this.$route);
        if (this.$route.query.projectid) {
            this.task.projectid = this.$route.query.projectid
            this.task.projectversion = this.$route.query.version
        }
    },
}
</script>
<style scoped>
@import url('../../../node_modules/animate.css/animate.min.css');

.step {
    width: 100%;
    display: flex;
    align-items: center;
    justify-content: center;
}

.box-card {
    width: 100%;
    height: 598px;
    margin-left: 1%;
}

.cardheader {
    display: flex;
    justify-content: left;
    padding-left: 15px;
    align-items: center;
    font-size: 25px;
}

.form {
    font-size: 30px;
    padding: 15px;
}

.formitem {
    width: 60%;
    text-align: left;

}

.pic {
    margin-top: 80px;
}

/deep/.el-upload-list,
.el-upload-list--text {
    width: 20%;
}

.labelblock {
    border: 1px solid rgb(221, 221, 221);
    display: flex;
    justify-content: left;
    align-items: center;
    height: 30px;
    width: 200px;
    padding-left: 5px;
    cursor: pointer;
}

.labelblock:hover {
    border: 1px solid rgb(36, 104, 242);
}

.labelicon {
    margin-left: 12px;
    cursor: pointer;
}

.labelicon:hover {
    color: rgb(36, 104, 242);
}

/deep/.el-card__body {
    padding: 8px;
}

/deep/.el-card__header {
    padding: 8px;
}

@keyframes shake {
    0% {
        transform: translate(0, 0);
    }

    10% {
        transform: translate(-5px, -5px);
    }

    20% {
        transform: translate(5px, 5px);
    }

    30% {
        transform: translate(-5px, -5px);
    }

    40% {
        transform: translate(5px, 5px);
    }

    50% {
        transform: translate(-5px, -5px);
    }

    60% {
        transform: translate(5px, 5px);
    }

    70% {
        transform: translate(-5px, -5px);
    }

    80% {
        transform: translate(5px, 5px);
    }

    90% {
        transform: translate(-5px, -5px);
    }

    100% {
        transform: translate(0, 0);
    }
}

#repeattext {
    animation: shake 0.8s 1 forwards;
    color: red;
    font-size: 12px;
    text-align: left;
}

.suretext {
    color: rgb(192, 196, 204);
    font-size: 12px;
    text-align: left;
}

.addok {
    color: green;
}

.input {
    width: 70%;
    height: 25px;
    padding: 0;
}

.inputlabel {
    width: 198px;
    height: 28px;
    display: flex;
    justify-content: left;
    align-items: center;
    padding-left: 5px;
    border-radius: 0px;
    border: 1px solid rgb(221, 221, 221);
    outline-style: none;
    font-size: 14px;
}

.inputlabel:focus {
    border: 1px solid rgb(36, 104, 242);
}

.repeatlabel {
    animation: shake 0.8s 1 forwards;
    border: 1px solid red;
    color: red;
}
</style>