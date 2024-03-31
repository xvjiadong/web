<template>
	<div style="text-align: left;padding-left: 40px;margin-top: 2px;box-shadow: 7px 7px 12px rgba(0, 0, 0, 0.4),
      -7px -7px 12px rgba(255, 255, 255, 0.9);display: flex;" v-loading="loading" element-loading-text="拼命加载中">
		<el-card class="teachcard2">
			<div slot="header">
				<el-page-header @back="goBack" :content="`${project.taskName} ${project.version}`">
				</el-page-header>
			</div>
			<div style="display: flex;flex-direction: column;">
				<span>
					项目所有人:{{ project.adminNane }}
				</span>
				<span>
					项目名称:{{ project.projectName }}
				</span>
				<span>
					项目版本:{{ project.version }}
				</span>
				<span>
					标注进度:15/200
				</span>
				<span>
					标注模式:{{ mode === 1 ? '长文本字段标注' : (mode === 2 ? '标签证据字段标注' : (mode === 3 ? "关联关系字段标注" : "智能标注")) }}
				</span>
			</div>
		</el-card>
		<el-popover v-model="vis" trigger="manual" width="250" ref="popover">
			<div v-if="mode == 2">
				<div v-if='mouseover'>
					<el-radio v-model="mode2type" label="1">标签</el-radio>
					<el-radio v-model="mode2type" label="2">证据</el-radio>
				</div>
				<el-divider direction="vertical"></el-divider>
				<div>
					<div v-if="mode2type === '1'">
						<div>
							<div style="height: 100px;overflow-y: scroll;">
								<div :key="tag.tag" v-for="tag in dynamicTags">
									标签名：
									<el-tag @close="handleClose(tag)" closable :disable-transitions="false">
										{{ tag.tag }}
									</el-tag>
									<div>证据列表:</div>
									<div :key="index" v-for="(evidence, index) in tag.evidence" class="evidence">
										<span @click="jump(`#${evidence}-0`)">{{ evidence }}</span>
									</div>
									<div v-if="tag.evidence.length == 0">
										无证据标注
									</div>
									<el-divider></el-divider>
								</div>
							</div>
							<div>
								<el-select filterable multiple collapse-tags class="input-new-tag" v-if="selectVisible"
									v-model="selectValue" ref="saveTagselect" size="small"
									@keyup.enter.native="handleSelectConfirm" @visible-change="blurs">
									<el-option v-for="item in options" :key="item.value" :label="item.label"
										:value="item.value">
									</el-option>
								</el-select>
								<el-button v-else class="button-new-tag" size="small"
									@click="showSelect">+已有标签</el-button>
								<el-input class="input-new-tag" v-if="inputVisible" v-model="inputValue"
									ref="saveTagInput" size="small" @keyup.enter.native="handleInputConfirm"
									@blur="handleInputConfirm">
								</el-input>
								<el-button v-else class="button-new-tag" size="small"
									@click="showInput">+新标签</el-button>
							</div>
						</div>
						<div v-if="popbutton">
							<el-button @click="tagok">确定</el-button>
							<el-button @click="cancelselect">取消</el-button>
						</div>
					</div>
					<div v-if="mode2type === '2'">
						<div style="height:50px;overflow-y: scroll;">
							<div>证据所属：</div>
							<span @click="jump(`#${linkevidence.id}-0`)" class="evidence">{{ linkevidence.id }}</span>
							<el-tag :disable-transitions="false">
								{{ linkevidence.tag }}
							</el-tag>
						</div>
						<div v-if="popbutton">
							<el-input size="small" v-model="linkpage" placeholder="请输入页数"></el-input>
							<el-select size="small" v-model="evidencetomark">
								<el-option v-for="item in evidencelist" :key="item.id" :label="item.id"
									:value="item"></el-option>
							</el-select>
							<el-select size="small" v-model="evidencetotag" :disabled="(evidencetomark === '')">
								<el-option v-for="item in taglist" :key="item" :label="item" :value="item"></el-option>
							</el-select>
							<el-button @click="evidenceok">确定</el-button>
							<el-button @click="cancelevidence">取消</el-button>
						</div>
					</div>
				</div>
			</div>
			<div v-if="mode === 3">
				<div style="height: 130px;overflow-y: auto;">
					<div>
						<div>
							<el-tag v-if="mode3tag !== ''">{{ mode3tag }}</el-tag>
						</div>
						<el-select filterable class="input-new-tag" v-if="mode3selectVisible" v-model="mode3selectValue"
							ref="mode3saveTagselect" size="small" @keyup.enter.native="mode3handleSelectConfirm"
							@visible-change="mode3blurs">
							<el-option v-for="item in mode3options" :key="item.value" :label="item.value"
								:value="item.value">
							</el-option>
						</el-select>
						<el-button v-else class="button-new-tag" size="small" @click="mode3showSelect">+已有实体</el-button>
						<el-input class="input-new-tag" v-if="mode3inputVisible" v-model="mode3inputValue"
							ref="mode3saveTagInput" size="small" @keyup.enter.native="mode3handleInputConfirm"
							@blur="mode3handleInputConfirm">
						</el-input>
						<el-button v-else class="button-new-tag" size="small" @click="mode3showInput">+ 新实体</el-button>
					</div>
					<el-divider></el-divider>
					<div>
						关系实体:
						<div v-for="(item, index) in mode3link" :key="`${item.id}+${index}`"
							style="display: flex;align-items: center;">
							<span>{{ item.linkname }}</span>
							<div style="width: 15px;height: 1px;background-color: rgb(100,100,101);"></div>
							<div
								style="position: relative;width: 24px;height: 20px;border-top: 1px solid rgb(100,100,101);border-left: 1px solid rgb(100,100,101); border-bottom: 1px solid rgb(100,100,101);">
							</div>
							<div class="linkright">
								<div class="righttext">
									<span @click="jump(`#${item.id}-0`)" class="evidence">{{ item.id + "-" + item.tag
										}}</span>
								</div>
								<div class="righttext">
									{{ mode3tag }}
								</div>
							</div>
						</div>
						<el-select size="small" v-model="chooselink">
							<el-option v-for="item in mode3linklist" :key="item.id" :label="`${item.id}-${item.tag}`"
								:value="item"></el-option>
						</el-select>
						<el-select size="small" v-model="linkname" :disabled="(chooselink === '')">
							<el-option v-for="item in linklist" :key="item.value" :label="item.value"
								:value="item.value"></el-option>
						</el-select>
						<el-button @click="addlink"
							:disabled="linkname === '' || chooselink === '' || mode3tag === ''">添加关系</el-button>
					</div>
				</div>
				<div v-if="!this.mode3mouseover">
					<el-button @click="mode3ok">确定</el-button>
					<el-button @click="mode3cancel">取消</el-button>
				</div>
			</div>
			<div v-if="mode === 4">
				<el-select @change="mode4select" v-model="smarttask" size="mini" placeholder="请选择智能标注任务">
					<el-option v-for="item in mode4list" :key="item.value" :value="item.value"
						:label="item.label"></el-option>
				</el-select>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '文本分类'">
					<el-select size="mini" v-model="mode41" multiple collapse-tags placeholder="请选择文本分类类别">
						<el-option v-for="item in classification" :key="item.id" :value="item.labels"
							:label="item.labels"></el-option>
					</el-select>
				</div>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '关键词识别'">
					<el-input size="mini" v-model="mode42" placeholder="请输入待识别关键词"></el-input>
				</div>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '情感分析'">
					<el-select size="mini" v-model="mode44" multiple collapse-tags placeholder="请选择分类类别">
						<el-option v-for="item in emotion" :key="item.value" :value="item.value"
							:label="item.value"></el-option>
					</el-select>
				</div>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '实体识别'">
					<el-input size="mini" v-model="mode45" placeholder="请输入待识别实体类型"></el-input>
				</div>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '意图识别'">
					<el-input size="mini" v-model="mode46" placeholder="请输入待识别意图"></el-input>
				</div>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '新闻分类'">
					<el-select size="mini" v-model="mode48" multiple collapse-tags placeholder="请选择新闻分类类别">
						<el-option v-for="item in newsclassification" :key="item.labels" :value="item.labels"
							:label="item.labels"></el-option>
					</el-select>
				</div>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '抽取式阅读理解'">
					<el-input size="mini" v-model="mode49" placeholder="请输入抽取问题"></el-input>
				</div>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '多项选择'">
					<el-input size="mini" v-model="mode410.question" placeholder="请输入问题"></el-input>
					<el-input size="mini" v-model="mode410.answer" placeholder="请输入选项,不同选项之间用/分隔"></el-input>
				</div>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '自然语言推理'">
					<el-input size="mini" v-model="mode411.sentence1" placeholder="请划选语句1"></el-input>
					<el-input size="mini" v-model="mode411.sentence2" placeholder="请划选语句2"></el-input>
					<el-input size="mini" v-model="mode411.answer" placeholder="请输入推理选项,不同选项之间用/分隔"></el-input>
				</div>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '指代消解'">
					<el-input size="mini" v-model="mode412.question" placeholder="请输入问题"></el-input>
					<el-input size="mini" v-model="mode412.answer" placeholder="请输入问题选项,不同选项之间用/分隔"></el-input>
				</div>
				<div style="height: 50px;overflow-y: auto;" v-if="smarttask === '语义匹配'">
					<el-input size="mini" v-model="mode413.sentence1" placeholder="请划选语句1"></el-input>
					<el-input size="mini" v-model="mode413.sentence2" placeholder="请划选语句2"></el-input>
				</div>
				<div>
					<el-button type="primary" size="mini" @click="mode4sure">确定</el-button>
					<el-button size="mini" @click="mode4cancel">取消</el-button>
				</div>
			</div>
			<iframe v-if="$store.state.pdflist.length > 0" slot="reference" ref="a"
				:src="`/pdfjs/web/viewer.html?file=${$store.state.pdflist[$store.state.index].url}`" width="830"
				height="650"></iframe>
		</el-popover>
		<el-card class="teachcard">
			<div slot="header" class="resultheader">
				<div style="color: #666;font-size: 20px;padding: 5px;font-weight: 600;">标注结果</div>
			</div>
			<el-collapse style="overflow-y: scroll;height: 530px;">
				<el-collapse-item v-for="item in markdata" :key="item.page">
					<template slot="title">
						第{{ item.page }}页
					</template>
					<div v-for="mark in item.mark" :key="mark.id">
						<div class="result" v-if="mark.mode === 1">
							<span>标注ID:{{ mark.id }}</span>
							<span>标注模式:长文本字段标注</span>
							<span
								style="width: 150px; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">标注内容:{{
		mark.choosecontent }}</span>
						</div>
						<div class="result" v-if="mark.mode === 2">
							<span>标注ID:{{ mark.id }}</span>
							<span>标注模式:标签证据字段标注</span>
							<span
								style="width: 150px; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">标注内容:{{
		mark.choosecontent }}</span>
							<span>标注类型:{{ mark.istag ? "标签" : "证据" }}</span>
							<div v-if="mark.istag">
								<div :key="tag.tag" v-for="tag in mark.markcontent">
									标签名：
									<el-tag :disable-transitions="false" size="mini">
										{{ tag.tag }}
									</el-tag>
									<div>证据列表:</div>
									<div :key="index" v-for="(evidence, index) in tag.evidence" class="evidence">
										<span @click="jump(`#${evidence}-0`)">{{ evidence }}</span>
									</div>
									<div v-if="tag.evidence.length == 0">
										无证据标注
									</div>
									<el-divider></el-divider>
								</div>
							</div>
							<div v-else>
								<div>
									<div>证据所属：</div>
									<span class="evidence">{{ mark.belong.id }}</span>
									<el-tag :disable-transitions="false" size="mini">{{ mark.belong.tag }}</el-tag>
								</div>
							</div>
						</div>
						<div class="result" v-if="mark.mode === 3">
							<span>标注ID:{{ mark.id }}</span>
							<span style="width: 150px; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">
								标注内容:{{ mark.choosecontent }}
							</span>
							<span>标注模式:关联关系字段标注</span>
							<span>关系实体:<el-tag size="mini" :disable-transitions="false">{{ mark.tag }}</el-tag></span>
							<div v-if="mark.link.length > 0">
								<div v-for="link in mark.link" :key="link.id"
									style="display: flex;align-items: center;">
									<span>{{ link.linkname }}</span>
									<div style="width: 15px;height: 1px;background-color: rgb(100,100,101);"></div>
									<div
										style="position: relative;width: 24px;height: 20px;border-top: 1px solid rgb(100,100,101);border-left: 1px solid rgb(100,100,101); border-bottom: 1px solid rgb(100,100,101);">
									</div>
									<div class="linkright">
										<div class="righttext">
											<span @click="jump(`#${link.id}-0`)" class="evidence">{{ link.tag
												}}</span>
										</div>
										<div class="righttext">
											{{ mark.tag }}
										</div>
									</div>
								</div>
							</div>
							<div v-else>无关联关系</div>
						</div>
						<div class="result" v-if="mark.mode === 4">
							<span>标注ID:{{ mark.id }}</span>
							<span>标注模式:智能标注</span>
							<span>标注类型:{{ mark.mode4kind }}</span>
							<span v-if="mark.mode4kind === '语义匹配' || mark.mode4kind === '自然语言推理'">
								<span
									style="width: 150px; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">
									标注内容1:{{ mark.choosecontent1 }}
								</span>
								<span
									style="width: 150px; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">
									标注内容2:{{ mark.choosecontent2 }}
								</span>
							</span>
							<span v-else
								style="width: 150px; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">
								标注内容:{{ mark.choosecontent }}
							</span>
							<span>标注结果:{{ mark.markcontent }}</span>
						</div>
					</div>
				</el-collapse-item>
			</el-collapse>
		</el-card>
	</div>
</template>
<script>
//import JsonData from '/public/TextMark.json'
import axios from 'axios'
//import FileSaver from "file-saver";
export default {
	data() {
		return {
			pdflist: [
			],
			project: {},
			pageNo: null,
			pdfPageNumber: 0,
			pdfTotalPages: 1,
			renderingPage: false,
			pdfData: null, // PDF的base64
			scale: 1.5,
			doc: "",
			docselection: "",
			x: "",
			x2: "",
			width: "",
			y: "",
			height: "",
			loading: true,
			currentPage: 1,
			markpage: [],
			pageheight: 0,
			pagewidth: 0,
			mode: 1,
			/*mode2状态变量*/
			vis: false,
			dynamicTags: [],
			selectValue: [],
			selectVisible: false,
			inputVisible: false,
			inputValue: '',
			markdata: [],
			options: [{
				value: '合同类型',
				label: '合同类型'
			}, {
				value: '基金类型',
				label: '基金类型'
			}, {
				value: '具体项目条款',
				label: '具体项目条款'
			}, {
				value: '合同描述',
				label: '合同描述'
			}, {
				value: '生效时机',
				label: '生效时机'
			}
			],
			marklist: [],
			id: '',
			etarget: "",
			popbutton: true,
			nowmode2showpage: "",
			nowmode2showmarkid: "",
			mode2type: "1",
			linkpage: "",
			evidencetomark: "",
			evidencetotag: "",
			linkevidence: "",
			mouseover: true,
			tagevidence: "",
			/*mode3状态变量*/
			mode3selectValue: [],
			mode3selectVisible: false,
			mode3inputVisible: false,
			mode3inputValue: '',
			mode3options: [{
				value: '类型',
				label: '类型'
			}, {
				value: '条款',
				label: '条款'
			}, {
				value: '原因',
				label: '原因'
			}, {
				value: '法规',
				label: '法规'
			}, {
				value: '金额',
				label: '金额 '
			}
			],
			mode3tag: "",
			mode3link: [],
			linklist: [
				{
					value: "解释",
					label: "解释"
				},
				{
					value: "目的",
					label: "目的"
				},
				{
					value: "属性",
					label: "属性"
				},
				{
					value: "从属",
					label: "从属"
				}
			],
			chooselink: "",
			linkname: "",
			mode3mouseover: "",
			chooosecontent: "",
			/*******************mode4变量**********************/
			mode4list: [{ label: "文本分类", value: "文本分类" }, { label: "关键词识别", value: "关键词识别" }, { label: "关键词抽取", value: "关键词抽取" }, { label: "情感分析", value: "情感分析" }, { label: "实体识别", value: "实体识别" }, { label: "意图识别", value: "意图识别" }, { label: "生成式摘要", value: "生成式摘要" }, { label: "新闻分类", value: "新闻分类" }, { label: "抽取式阅读理解", value: "抽取式阅读理解" }, { label: "多项选择", value: "多项选择" }, { label: "自然语言推理", value: "自然语言推理" }, { label: "指代消解", value: "指代消解" }, { label: "语义匹配", value: "语义匹配" }],
			smarttask: "",
			/*文本分类变量 */
			mode41: [],
			classification: [{ labels: "财经", id: 1 }, { labels: "军事", id: 2 }, { labels: "政治", id: 3 }, { labels: "文化", id: 4 }, { labels: "社会", id: 5 },],
			/*关键词识别变量 */
			mode42: "",
			/*情感分析变量 */
			mode44: [],
			emotion: [{ value: "开心" }, { value: "激动" }, { value: "伤心" }, { value: "沮丧" }, { value: "烦闷" }],
			/*实体识别变量 */
			mode45: "",
			/*意图识别变量 */
			mode46: "",
			/*新闻分类变量 */
			mode48: [],
			newsclassification: [{ labels: "财经", id: 1 }, { labels: "军事", id: 2 }, { labels: "政治", id: 3 }, { labels: "文化", id: 4 }, { labels: "社会", id: 5 }],
			/*抽取式阅读理解变量 */
			mode49: "",
			/*多项选择变量 */
			mode410: { question: "", answer: "" },
			/*自然语言推理变量 */
			mode411: { sentence1: "", sentence2: "", answer: "" },
			/*指代消解变量 */
			mode412: { question: "", answer: "" },
			/*语义匹配变量 */
			mode413: { sentence1: "", sentence2: "", answer: "" },
		}
	},
	computed: {
		evidencelist() {
			if (this.linkpage) {
				let a = this.markdata.filter(item => {
					return item.page === this.linkpage
				})
				if (a.length > 0) {
					let c = []
					a[0].mark.forEach(item2 => {
						if (item2.mode === 2 && item2.istag === true) {
							c.push(item2)
						}
					})
					return c
				}
				return []
			} else {
				let a = []
				this.markdata.forEach(item => {
					item.mark.forEach(item2 => {
						if (item2.mode === 2 && item2.istag === true) {
							a.push(item2)
						}
					})
				})
				return a
			}
		},
		taglist() {
			console.log(this.evidencetomark);
			let a = []
			if (this.evidencetomark === "") {
				return []
			}
			this.evidencetomark.markcontent.map(item => {
				a.push(item.tag)
			})
			return a
		},
		mode3linklist() {
			let c = []
			this.markdata.forEach(item => {
				item.mark.forEach(item2 => {
					if (item2.mode === 3 && item2.id !== this.mode3mouseover) {
						c.push({ id: item2.id, tag: item2.tag })
					}
				})
			})
			return c
		}
	},
	watch: {
		currentPage: {
			deep: true,
			handler() {
				setTimeout(() => {
					this.keepmark()
				}, 500);
			}
		}
	},
	mounted() {
		//console.log(JsonData);
		this.project = this.$route.query;
		//this.smartmark("抽取式阅读理解任务：阅读文章【谷歌公司首席执行官表示，他们计划在未来五年内全面实现碳中和，并将投资额翻倍用于太阳能和风能等清洁能源项目。同时，亚马逊也发布了雄心勃勃的计划，承诺在2030年前投资100亿美元用于推动可再生能源的创新和发展。】问题【谷歌公司的目标是什么】的答案是什么？")
		if (this.$store.state.pdflist.length === this.$store.state.index) {
			this.$store.commit("setpdflist", { url: "https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2023-11-24/ae18f0d1535b48418341c1de5ed09964-信息抽取标注/V1/1.pdf", mark: "https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2023-11-24/ae18f0d1535b48418341c1de5ed09964-信息抽取标注/V1/1.json" })
			this.getmark(this.$store.state.pdflist[this.$store.state.index].mark)
			/*axios.post("http://120.26.142.114:10010/dataset/task", { version: this.project.versionId, page: Math.floor(this.$store.state.index / 5) + 1, number: 5 }).then(res => {
				console.log(res.data);
				res.data.data.map(item => {
					this.$store.commit("setpdflist", item)
				})
				console.log(this.$store.state.pdflist[this.$store.state.index].mark);
				this.getmark(this.$store.state.pdflist[this.$store.state.index].mark)
			}).catch(e => {
				console.log(e);
			})*/
		} else {
			this.getmark(this.$store.state.pdflist[this.$store.state.index].mark)
		}
		setTimeout(() => {
			this.doc = this.$refs.a
			this.docselection = this.doc.contentWindow
			this.$nextTick(() => {
				this.choose()
				this.keepmark()
				setTimeout(() => {
					this.pageheight = parseFloat(this.doc.contentDocument.getElementsByClassName("page")[0].style.height.split("*")[1].split("px")[0])
					this.pagewidth = parseFloat(this.doc.contentDocument.getElementsByClassName("page")[0].style.width.split("*")[1].split("px")[0])
				}, 5000)

			})
			//console.log(this.markpage);
			//this.drawline(JsonData[0].page,JsonData[0].mark[0].shape)
		}, 5000)

	},
	methods: {
		getmark(item) {
			console.log(item);
			axios.get(item).then(res => {
				console.log(res.data);
				if (typeof res.data === "string") {
					this.markdata = []
				} else {
					this.markdata = res.data
				}

			})
		},
		mode4select(item) {
			if (item === "自然语言推理") {
				if (this.mode411.sentence1 === "") {
					this.mode411.sentence1 = this.docselection.getSelection().getRangeAt(0).toString()
				} else {
					this.mode411.sentence2 = this.docselection.getSelection().getRangeAt(0).toString()
				}
			} else if (item === "语义匹配") {
				if (this.mode413.sentence1 === "") {
					this.mode413.sentence1 = this.docselection.getSelection().getRangeAt(0).toString()
				} else {
					this.mode413.sentence2 = this.docselection.getSelection().getRangeAt(0).toString()
				}
			}
		},
		mode4sure() {
			let a
			if (this.smarttask === "文本分类") {
				a = `${this.smarttask}任务；【${this.docselection.getSelection().getRangeAt(0).toString()}】`
				if (this.mode41.length === 0) {
					this.$message.warning("请选择至少一个类别")
					return
				}
				a += `这篇文章的类别是什么？{${this.mode41.join("/")}}`
			} else if (this.smarttask === "关键词识别") {
				a = `${this.smarttask}任务；【${this.docselection.getSelection().getRangeAt(0).toString()}】`
				if (this.mode42 === "") {
					this.$message.warning("请输入待识别关键词")
					return
				}
				a += `问题【${this.mode42}】`
			} else if (this.smarttask === "关键词抽取") {
				a = `${this.smarttask}任务；【${this.docselection.getSelection().getRangeAt(0).toString()}】`
				a += "这篇文章的关键词是什么？"
			} else if (this.smarttask === "情感分析") {
				a = `${this.smarttask}任务；【${this.docselection.getSelection().getRangeAt(0).toString()}】`
				if (this.mode44.length === 0) {
					this.$message.warning("请选择至少一个类别")
					return
				}
				a += `这篇文章的情感态度是什么？{${this.mode44.join("/")}}`
			} else if (this.smarttask === "实体识别") {
				a = `${this.smarttask}任务；找出【${this.docselection.getSelection().getRangeAt(0).toString()}】`
				if (this.mode45 === "") {
					this.$message.warning("请输入识别关键词类型")
					return
				}
				a += `这篇文章中所有【${this.mode45}】类型的实体？`
			} else if (this.smarttask === "意图识别") {
				a = `${this.smarttask}任务；【${this.docselection.getSelection().getRangeAt(0).toString()}】`
				if (this.mode46 === "") {
					this.$message.warning("请输入意图类型")
					return
				}
				a += `这句话的意图是什么？{${this.mode46}}`
			} else if (this.smarttask === "生成式摘要") {
				a = `${this.smarttask}任务；【${this.docselection.getSelection().getRangeAt(0).toString()}】`
				a += "这篇文章的摘要是什么？"
			} else if (this.smarttask === "新闻分类") {
				a = `${this.smarttask}任务；【${this.docselection.getSelection().getRangeAt(0).toString()}】`
				if (this.mode48.length === 0) {
					this.$message.warning("请选择至少一个类别")
					return
				}
				a += `这篇文章的类别是什么？{${this.mode48.join("/")}}`
			} else if (this.smarttask === "抽取式阅读理解") {
				a = `${this.smarttask}任务；阅读文章【${this.docselection.getSelection().getRangeAt(0).toString()}】`
				if (this.mode49 === "") {
					this.$message.warning("请输入问题")
					return
				}
				a = a + `问题【${this.mode49}】的答案是什么？`
			} else if (this.smarttask === "多项选择") {
				a = `${this.smarttask}任务；阅读文章【${this.docselection.getSelection().getRangeAt(0).toString()}】`
				if (this.mode410.question === "" || this.mode410.answer === "") {
					this.$message.warning("请输入问题和选项")
					return
				}
				a = a + `问题【${this.mode410.question}】？{${this.mode410.answer}}`
			} else if (this.smarttask === "自然语言推理") {
				if (this.mode411.sentence1 === "" || this.mode411.sentence2 === "" || this.mode411.answer === "") {
					this.$message.warning("请填写句子和逻辑选择")
					return
				}
				a = `${this.smarttask}任务；【${this.mode411.sentence1}】和【${this.mode411.sentence2}】，以上两句话的逻辑关系是什么？{${this.mode411.answer}}`
			} else if (this.smarttask === "指代消解") {
				if (this.mode412.question === "" || this.mode412.answer === "") {
					this.$message.warning("请填写问题和选项")
					return
				}
				a = `${this.smarttask}任务；文章【${this.docselection.getSelection().getRangeAt(0).toString()}】中{${this.mode412.question}}{${this.mode412.answer}}`
			} else if (this.smarttask === "语义匹配") {
				if (this.mode413.sentence1 === "" || this.mode413.sentence2 === "") {
					this.$message.warning("请填写匹配句子和匹配选项")
					return
				}
				a = `${this.smarttask}任务；【${this.mode413.sentence1}】和【${this.mode413.sentence2}】，以上两句话的内容是否相似？{相似/不相似}`
			}
			this.smartmark(a)
		},
		mode4cancel() {
			this.vis = false
			if (this.smarttask === "文本分类") {
				this.mode41 = []
			} else if (this.smarttask === "关键词识别") {
				this.mode42 = ""
			} else if (this.smarttask === "情感分析") {
				this.mode44 = []
			} else if (this.smarttask === "实体识别") {
				this.mode45 = ""
			} else if (this.smarttask === "意图识别") {
				this.mode46 = ""
			} else if (this.smarttask === "新闻分类") {
				this.mode48 = []
			} else if (this.smarttask === "抽取式阅读理解") {
				this.mode49 = ""
			} else if (this.smarttask === "多项选择") {
				this.mode410 = { question: "", answer: "" }
			} else if (this.smarttask === "自然语言推理") {
				this.mode411 = { sentence1: "", sentence2: "", answer: "" }
			} else if (this.smarttask === "指代消解") {
				this.mode412 = { question: "", answer: "" }
			} else if (this.smarttask === "语义匹配") {
				this.mode413 = { sentence1: "", sentence2: "", answer: "" }
			}
			this.smarttask = ""
		},
		smartmark(item) {
			axios.post("http://192.168.224.19:3000/predict/", { text: item }, { timeout: 5000000000000000 }).then(res => {
				console.log(res.data);
				const regex = /【(.*?)】/g;
				const matches = [];
				let match;
				while ((match = regex.exec(item)) !== null) {
					matches.push(match[1]); // 将匹配到的内容存入数组
				}
				let result = { markcontent: res.data.prediction[0], id: this.id, mode: 4, mode4kind: this.smarttask }
				if (item.split("任务")[0] === "自然语言推理" || item.split("任务")[0] === "语义匹配") {
					result.choosecontent1 = matches[0]
					result.choosecontent2 = matches[1]
				} else {
					result.choosecontent = matches[0]
				}
				let ispage = false
				this.markdata.map(item => {
					if (item.page === this.id.split("-")[0]) {
						ispage = true
						item.mark.push(result)
					}
				})
				if (!ispage) {
					let c = []
					c.push(result)
					let a = { page: this.id.split("-")[0], mark: c }
					this.markdata.push(a)
				}
				this.etarget = ""
				this.id = ""
				this.mode4cancel()
			}).catch(e => {
				console.log(e);
			})
		},
		goBack() {
			let a = JSON.stringify(this.markdata)
			let file = new FormData()
			const blob = new Blob([a]);
			file.set("file", blob, "data.json")
			file.set("id", this.$store.state.pdflist[this.$store.state.index].id)
			axios.put("http://120.26.142.114:10010/dataset/call", file, { headers: { "Content-Type": "multipart/form-data;charset=utf-8" } }).then((res) => {
				console.log(res.data);
				this.$router.push("/MakeMark")
			})
		},
		addlink() {
			let c = { linkname: this.linkname, id: this.chooselink.id, tag: this.chooselink.tag }
			let isadd = false
			this.mode3link.forEach((item) => {
				if (item.id === c.id && item.linkname === c.linkname) {
					isadd = true
				}
			})
			if (!isadd) {
				this.mode3link.push(c)
				this.linkname = ""
				this.chooselink = ""
			} else {
				this.$message({ type: "warning", message: "重复添加关系" })
			}
		},
		mode3ok() {
			if (this.mode3tag) {
				this.drawline(this.parentpage(this.etarget), this.marklist, this.id, this.mode, null, null, null, 0, this.mode3tag, this.mode3link)
			} else {
				this.$message({ type: "warning", message: "请命名端点实体" })
			}
		},
		mode3cancel() {
			this.mode3tag = ""
			this.mode3link = ""
			this.vis = false
		},
		mode3blurs(e) {
			console.log(e);
			if (!e) {
				this.mode3handleSelectConfirm()
			}
		},
		mode3showSelect() {
			this.mode3selectVisible = true;
			this.$nextTick(() => {
				//this.$refs.saveTagInput.toggleMenu()
			})
		},
		mode3handleSelectConfirm() {
			let selectValue = this.mode3selectValue;
			//console.log(this.selectValue);
			if (!this.mode3mouseover) {
				if (selectValue) {
					this.mode3tag = selectValue;
				}
			} else {
				this.markdata.forEach()
			}

			this.mode3selectVisible = false;
			this.mode3selectValue = '';
		},
		mode3showInput() {
			this.mode3inputVisible = true;
			this.$nextTick(() => {
				//this.$refs.mode3saveTagInput.$refs.input.focus();
			});
		},
		mode3handleInputConfirm() {
			let inputValue = this.mode3inputValue;
			if (inputValue) {
				this.mode3tag = inputValue;
			}
			this.mode3inputVisible = false;
			this.mode3inputValue = '';
		},
		jump(href) {
			let a = this.doc.contentDocument.createElement("a")
			if (this.doc.contentDocument.querySelector("#page" + href.substring(1, 2)).querySelector(".textLayer")) {
				a.href = href
				a.click()
				a.remove()
			} else {
				a.href = "#page" + href.substring(1, 2)
				a.click()
				a.remove()
			}
		},
		evidenceok() {
			if (this.evidencetomark !== "") {
				this.drawline(this.parentpage(this.etarget), this.marklist, this.id, this.mode, null, false, { id: this.evidencetomark.id, tag: this.evidencetotag }, 0)
				this.$nextTick(() => {
					this.evidencetomark = ""
					this.evidencetotag = ""
					this.linkevidence = {}
					this.linkpage = ""
					this.marklist = []
					this.id = ''
					this.etarget = ""
				})
			} else {
				this.$message({ type: "warning", message: "请选择证据信息" })
				this.$nextTick(() => {
					this.marklist = []
					this.id = ''
					this.etarget = ""
					this.inputValue = ''
					this.selectValue = []
					this.dynamicTags = []
				})
			}

		},
		tagok() {
			if (this.dynamicTags.length > 0) {
				console.log(this.id);
				this.drawline(this.parentpage(this.etarget), this.marklist, this.id, this.mode, this.dynamicTags, true, null, 0)
				this.$nextTick(() => {
					this.marklist = []
					this.id = ''
					this.etarget = ""
					this.inputValue = ''
					this.selectValue = []
					this.dynamicTags = []
				})
			} else {
				this.$message({ type: "warning", message: "请选择标签信息" })
				this.$nextTick(() => {
					this.marklist = []
					this.id = ''
					this.etarget = ""
					this.inputValue = ''
					this.selectValue = []
					this.dynamicTags = []
				})
			}
		},
		cancelselect() {
			this.dynamicTags = []
			this.selectValue = []
			this.inputValue = ""
			this.$nextTick(() => {
				this.vis = false
			})
		},
		cancelevidence() {
			this.evidencetomark = ""
			this.evidencetotag = ""
			this.linkpage = ""
			this.$nextTick(() => {
				this.vis = false
			})
		},
		blurs(e) {
			console.log(e);
			if (!e) {
				this.handleSelectConfirm()
			}
		},
		handleClose(tag) {
			this.dynamicTags.splice(this.dynamicTags.indexOf(tag), 1);
			if (!this.popbutton) {
				this.markdata.forEach(item => {
					if (item.page === this.nowmode2showpage) {
						item.mark.forEach(item2 => {
							if (item2.id === this.nowmode2showmarkid) {
								item2.markcontent = this.dynamicTags
							}
						})
					}
				})
			}
		},
		showSelect() {
			this.selectVisible = true;
			this.$nextTick(() => {
				//this.$refs.saveTagInput.toggleMenu()
			})
		},
		handleSelectConfirm() {
			let selectValue = this.selectValue;
			//console.log(this.selectValue);
			if (selectValue.length > 0) {
				selectValue.map(item => {
					this.dynamicTags.push({ tag: item, evidence: [] });
				})
			}
			this.selectVisible = false;
			this.selectValue = '';
		},
		showInput() {
			this.inputVisible = true;
			this.$nextTick(() => {
				this.$refs.saveTagInput.$refs.input.focus();
			});
		},
		handleInputConfirm() {
			let inputValue = this.inputValue;
			if (inputValue) {
				this.dynamicTags.push({ tag: inputValue, evidence: [] });
			}
			this.inputVisible = false;
			this.inputValue = '';
		},
		setmode(mode) {
			this.mode = mode

		},
		percenttopx(element, number) {
			let a = parseFloat(element.split("%")[0]) / 100
			let b = 'calc(var(--scale-factor) *' + number * a + "px)"
			return b
		},
		keepmark() {
			let a = this.getTextLayer()
			this.markdata.forEach(item => {
				if (a.includes(item.page)) {
					item.mark.forEach(item2 => {
						if (item2.mode === 1) {
							this.drawline(item.page, item2.shape, item2.id, item2.mode, null, null, null, 1)
						} else if (item2.mode === 2) {
							this.drawline(item.page, item2.shape, item2.id, item2.mode, item2.markcontent, item2.istag, item2.belong, 1)
						} else if (item2.mode === 3) {
							this.drawline(item.page, item2.shape, item2.id, item2.mode, null, null, null, 1, item2.tag, item2.link)
						}
					})
				}
			})
		},
		getTextLayer() {
			let newmarkpage = []
			let newdrawpage = []
			let a = this.doc.contentDocument.getElementsByClassName("textLayer")
			for (let i = 0; i < a.length; i++) {
				if (!this.markpage.includes(a[i].parentNode.getAttribute("data-page-number"))) {
					newdrawpage.push(a[i].parentNode.getAttribute("data-page-number"))
				}
				newmarkpage.push(a[i].parentNode.getAttribute("data-page-number"))
			}
			this.markpage = newmarkpage
			return newdrawpage
		},
		go() {
			//let a = e.target
			let b = document.createElement("a")
			b.setAttribute("href", "#page1")
			//console.log(this.$refs.a.contentWindow);
			this.$refs.a.contentDocument.getElementById("viewerContainer").appendChild(b);
			//b.click()
			b.remove()
		},
		drawline(page, shape, id, mode, markcontent = null, istag = null, belong = null, isadd, mode3tag = null, mode3link = null) {
			const parent = this.doc.contentDocument.querySelectorAll("div[data-page-number='" + page + "'].page")[0];
			if (mode === 1) {
				let newshape = []
				let newparentdiv = document.createElement("div")
				newparentdiv.setAttribute("id", id)
				shape.forEach((item, index) => {
					let newchilddiv = document.createElement("div")
					let newmarklist = { width: item.width, height: item.height, left: item.left, top: item.top, id: item.id }
					newchilddiv.style.position = "absolute"
					newchilddiv.style.zIndex = "1"
					newchilddiv.style.borderRadius = "2px"
					newchilddiv.style.backgroundColor = "rgba(235,73,73,0.8)"
					newchilddiv.style.width = item.width
					newchilddiv.style.height = item.height
					newchilddiv.style.top = item.top
					newchilddiv.style.left = item.left
					newchilddiv.setAttribute("id", id + "-" + index)
					if (item.width.match(/\d+/g).map(Number)[0] + item.left.match(/\d+/g).map(Number)[0] < 793.6) {
						//console.log(newdiv);
						newshape.push(newmarklist)
						newparentdiv.appendChild(newchilddiv)
					}
				})
				let newmark = { mode: 1, id: id, shape: newshape, choosecontent: this.choosecontent }
				let ispageset = false
				if (isadd === 0) {
					this.markdata.map(item => {
						if (item.page === page) {
							ispageset = true
							item.mark.push(newmark)
						}
					})
					if (!ispageset) {
						let a = []
						a.push(newmark)
						let newpage = { page: page, mark: a }
						this.markdata.push(newpage)
					}
				}
				parent.appendChild(newparentdiv)
				//console.log(this.markdata);
			} else if (mode === 2) {
				//console.log(2);
				let newshape = []
				let newparentdiv = document.createElement("div")
				newparentdiv.setAttribute("id", id)
				shape.forEach((item, index) => {
					if (index === 0) {
						let childbutton = document.createElement("button")
						childbutton.style.position = "absolute"
						childbutton.style.zIndex = "3"
						childbutton.style.borderRadius = "2px"
						childbutton.style.width = "16px"
						childbutton.style.height = "16px"
						childbutton.style.left = item.left.includes("*") ? "calc(var(--scale-factor)*" + (parseFloat(item.left.split("*")[1].split("px")[0]) - 10) + "px)" : (parseFloat(item.left.split("px")[0] - 10)) + "px"
						childbutton.style.top = item.top.includes("*") ? "calc(var(--scale-factor)*" + (parseFloat(item.top.split("*")[1].split("px")) - 11.54) + "px)" : (parseFloat(item.top.split("px")[0] - 1)) + "px"
						childbutton.innerHTML = istag ? "|" : "—"
						childbutton.style.textAlign = "center"
						childbutton.style.padding = "0"
						childbutton.style.margin = "0"
						childbutton.setAttribute("id", id + "-" + "button")
						if (istag) {
							childbutton.addEventListener("mouseover", (e) => {
								this.mode = 2
								this.docselection.that.changemode(2)
								this.popoverposition(e)
								this.popbutton = false
								this.mouseover = false
								this.mode2type = "1"
								this.$nextTick(() => {
									this.vis = true
									let page = this.parentpage(e.target)
									this.nowmode2showpage = page
									this.nowmode2showmarkid = e.target.getAttribute("id").slice(0, -7)
									this.markdata.forEach(item => {
										if (item.page === page) {
											item.mark.forEach(item2 => {
												if (item2.id === e.target.getAttribute("id").slice(0, -7)) {
													this.dynamicTags = item2.markcontent
												}
											})
										}
									})

								})
							})
						} else {
							childbutton.addEventListener("mouseover", (e) => {
								this.mode = 2
								this.docselection.that.changemode(2)
								this.popoverposition(e)
								this.popbutton = false
								this.mouseover = false
								this.mode2type = "2"
								this.$nextTick(() => {
									this.vis = true
									let page = this.parentpage(e.target)
									this.nowmode2showpage = page
									this.nowmode2showmarkid = e.target.getAttribute("id").slice(0, -7)
									this.markdata.forEach(item => {
										if (item.page === page) {
											item.mark.forEach(item2 => {
												if (item2.id === e.target.getAttribute("id").slice(0, -7)) {
													this.linkevidence = item2.belong
												}
											})
										}
									})
								})
							})
						}
						newparentdiv.appendChild(childbutton)
					}
					let newchilddiv = document.createElement("div")
					let newmarklist = { width: item.width, height: item.height, left: item.left, top: item.top, id: id + "-" + index }
					newchilddiv.style.position = "absolute"
					newchilddiv.style.zIndex = "1"
					newchilddiv.style.borderRadius = "2px"
					if (istag) {
						newchilddiv.style.border = "2px solid rgba(235,73,73,0.8)"
					} else {
						newchilddiv.style.borderBottom = "2px solid rgba(235,73,73,0.8)"
					}
					newchilddiv.style.width = item.width
					newchilddiv.style.height = item.height
					newchilddiv.style.top = item.top
					newchilddiv.style.left = item.left
					newchilddiv.setAttribute("id", id + "-" + index)
					if (item.width.match(/\d+/g).map(Number)[0] + item.left.match(/\d+/g).map(Number)[0] < 793.6) {
						//console.log(newdiv);
						newshape.push(newmarklist)
						newparentdiv.appendChild(newchilddiv)
					}
				})
				if (isadd === 0) {
					console.log("isadd");
					let newmark = {}
					if (istag) {
						newmark = { mode: 2, id: id, markcontent: markcontent, shape: newshape, istag: istag, choosecontent: this.choosecontent }
					} else {
						newmark = { mode: 2, id: id, markcontent: markcontent, shape: newshape, istag: istag, belong: belong, choosecontent: this.choosecontent }
					}
					let ispageset = false
					this.markdata.map(item => {
						if (item.page === page) {
							ispageset = true
							item.mark.push(newmark)
						}
						let linkadd = false
						if (belong !== null && item.page === belong.id.substring(0, 1)) {
							item.mark.forEach(item2 => {
								if (item2.id === belong.id) {
									item2.markcontent.forEach(item3 => {
										if (item3.tag === belong.tag) {
											linkadd = true
											item3.evidence.push(id)
										}
									})
									if (!linkadd) {
										let b = []
										b.push(id)
										let a = { tag: belong.tag, evidence: b }
										item2.markcontent.push(a)
									}
								}
							})
						}
					})
					if (!ispageset) {
						let a = []
						a.push(newmark)
						let newpage = { page: page, mark: a }
						this.markdata.push(newpage)
					}
				}
				parent.appendChild(newparentdiv)
				console.log(this.markdata);
				this.vis = false
				this.popbutton = true
			} else if (mode === 3) {
				let newshape = []
				let newparentdiv = document.createElement("div")
				newparentdiv.setAttribute("id", id)
				shape.forEach((item, index) => {
					if (index === 0) {
						let childbutton = document.createElement("button")
						childbutton.style.position = "absolute"
						childbutton.style.zIndex = "3"
						childbutton.style.borderRadius = "2px"
						childbutton.style.width = "16px"
						childbutton.style.height = "16px"
						childbutton.style.left = item.left.includes("*") ? "calc(var(--scale-factor)*" + (parseFloat(item.left.split("*")[1].split("px")[0]) - 10) + "px)" : (parseFloat(item.left.split("px")[0] - 10)) + "px"
						childbutton.style.top = item.top.includes("*") ? "calc(var(--scale-factor)*" + (parseFloat(item.top.split("*")[1].split("px")) - 11.54) + "px)" : (parseFloat(item.top.split("px")[0] - 1)) + "px"
						childbutton.innerHTML = "3"
						childbutton.style.textAlign = "center"
						childbutton.style.padding = "0"
						childbutton.style.margin = "0"
						childbutton.setAttribute("id", id + "-" + "button")
						childbutton.addEventListener("mouseover", (e) => {
							this.mode = 3
							this.docselection.that.changemode(3)
							this.mode3mouseover = id
							this.popoverposition(e)
							this.$nextTick(() => {
								this.vis = true
								this.markdata.forEach(item => {
									if (item.page === page) {
										item.mark.forEach(item2 => {
											if (item2.id === e.target.getAttribute("id").slice(0, -7)) {
												this.mode3tag = item2.tag
												this.mode3link = item2.link
											}
										})
									}
								})
							})
						})
						parent.appendChild(childbutton)
					}
					let newchilddiv = document.createElement("div")
					let newmarklist = { width: item.width, height: item.height, left: item.left, top: item.top, id: item.id }
					newchilddiv.style.position = "absolute"
					newchilddiv.style.zIndex = "1"
					newchilddiv.style.borderRadius = "2px"
					newchilddiv.style.borderTop = "2px solid rgba(235,73,73,0.8)"
					newchilddiv.style.width = item.width
					newchilddiv.style.height = item.height
					newchilddiv.style.top = item.top
					newchilddiv.style.left = item.left
					newchilddiv.setAttribute("id", id + "-" + index)
					if (item.width.match(/\d+/g).map(Number)[0] + item.left.match(/\d+/g).map(Number)[0] < 793.6) {
						//console.log(newdiv);
						newshape.push(newmarklist)
						newparentdiv.appendChild(newchilddiv)
					}
				})
				let newmark = { mode: 3, id: id, shape: newshape, tag: mode3tag, link: mode3link, choosecontent: this.choosecontent }
				if (isadd === 0) {
					this.mode3link.forEach(item => {
						this.markdata.forEach(item2 => {
							if (item2.page === item.id.split("-")[0]) {
								item2.mark.forEach(item3 => {
									console.log(item3.id, item.id);
									if (item3.id === item.id) {
										item3.link.push({ tag: mode3tag, id: id, linkname: item.linkname })
									}
								})
							}
						})
					})
				}

				let ispageset = false
				if (isadd === 0) {
					this.markdata.map(item => {
						if (item.page === page) {
							ispageset = true
							item.mark.push(newmark)
						}
					})
					if (!ispageset) {
						let a = []
						a.push(newmark)
						let newpage = { page: page, mark: a }
						this.markdata.push(newpage)
					}
				}
				parent.appendChild(newparentdiv)
				this.vis = false
				console.log(this.markdata);
				this.linkname = ""
				this.chooselink = ""
			}
		},
		//找当前标注标签的类名为page的父元素
		parentpage(node) {
			if (node.className === "page") {
				return node.getAttribute("data-page-number")
			} else {
				return this.parentpage(node.parentNode)
			}
		},
		choose() {
			let sel = this.doc.contentDocument
			this.$store.commit("setpdflist", this.pdflist)
			sel.getElementById("access").remove()
			sel.getElementById("viewerContainer").addEventListener("scroll", () => {
				let pdfInfo = this.docselection.PDFViewerApplication;
				if (pdfInfo.page !== this.currentPage) {
					this.currentPage = pdfInfo.page
				}
			})
			sel.getElementById("prepdf").addEventListener("click", () => { this.$store.commit("changeindex", { value: -1 }) })
			sel.getElementById("nextpdf").addEventListener("click", () => {
				/*let a = JSON.stringify(this.markdata)
				const blob = new Blob([a]);
				FileSaver.saveAs(blob, (this.$store.state.index + 1) + ".json")*/
				this.$store.commit("changeindex", { value: 1 })

			})
			sel.getElementById("mode1").addEventListener("click", () => {
				this.mode = 1
				this.docselection.that.changemode(1)
			})
			sel.getElementById("mode2").addEventListener("click", () => {
				this.mode = 2
				this.docselection.that.changemode(2)
			})
			sel.getElementById("mode3").addEventListener("click", () => {
				this.mode = 3
				this.docselection.that.changemode(3)
			})
			sel.getElementById("mode4").addEventListener("click", () => {
				this.mode = 4
				this.docselection.that.changemode(4)
			})
			for (let i = 0; i < sel.getElementsByClassName('page').length; i++) {
				sel.getElementsByClassName("page")[i].setAttribute("id", "page" + sel.getElementsByClassName("page")[i].getAttribute("data-page-number"))
				sel.getElementsByClassName('page')[i].addEventListener("mousedown", (e) => {
					this.vis = false
					this.popbutton = false
					this.dynamicTags = []
					this.selectValue = []
					this.inputValue = ""
					this.linkevidence = ""
					this.mode3link = []
					this.mode3tag = ""
					this.mode3mouseover = ""
					this.smarttask = ""
					if (!e.target.style.left) {
						return
					}
					if (e.target.style.left.includes("%")) {
						e.target.style.left = this.percenttopx(e.target.style.left, this.pagewidth)
					}
					if (e.target.style.top.includes("%")) {
						e.target.style.top = this.percenttopx(e.target.style.top, this.pageheight)
					}
					this.x = parseFloat(e.target.style.left.split("*")[1].split("px")[0])
					this.width = e.target.style.left.split("*")[0] + "*"
					this.y = e.target.style.top
					this.x2 = e.clientX
				}, true)
			}
			for (let i = 0; i < sel.getElementsByClassName('page').length; i++) {
				sel.getElementsByClassName('page')[i].addEventListener("mouseup", (e) => {
					this.choosecontent = this.docselection.getSelection().getRangeAt(0).toString()
					if (this.x2 === e.clientX || this.docselection.getSelection().getRangeAt(0).toString() === "") {
						return
					}
					if (this.docselection.getSelection().getRangeAt(0).cloneContents().childNodes[0].nodeName === '#text') {
						let shape = []
						let childline = { top: "", left: "", width: "", height: "" }
						childline.height = e.target.style.fontSize
						childline.top = this.y
						let id = this.parentpage(e.target) + "-" + Date.now()
						if (this.x2 < e.clientX) {
							childline.left = this.x2 - 10 + "px"
							childline.width = e.clientX - this.x2 + "px"
						} else {
							childline.left = e.clientX - 10 + "px"
							childline.width = this.x2 - e.clientX + "px"
						}
						shape.push(childline)
						//this.parentpage(e.target).appendChild(a)
						if (this.mode === 1) {
							this.drawline(this.parentpage(e.target), shape, id, this.mode, null, null, null, 0)
						} else if (this.mode === 2) {
							this.popoverposition(e)
							this.etarget = e.target
							this.marklist = shape
							this.id = id
							this.popbutton = true
							this.mouseover = true
							this.vis = true
						} else if (this.mode === 3) {
							this.popoverposition(e)
							this.etarget = e.target
							this.marklist = shape
							this.id = id
							this.vis = true
						} else if (this.mode === 4) {
							this.popoverposition(e)
							this.vis = true
						}
						return
					}
					let ispage = false
					let children = this.docselection.getSelection().getRangeAt(0).cloneContents().childNodes
					let marklist = []
					for (let i = 0; i < children.length; i++) {
						if (children[i].className === "page" || children[i].className === "textLayer") {
							ispage = true
							this.$message({ message: "不允许跨页标注", type: "warning" })
							break
						} else {
							let dir = [{ top: "", left: 999999, innerText: "", fontSize: 0 }]
							if (children[i].className === "") {
								//console.log(children[i]);
								if (children[i].innerHTML !== "") {
									if (children[i].style.left.includes("%")) {
										let a = parseFloat(children[i].style.left.split("%")[0]) / 100
										children[i].style.left = 'calc(var(--scale-factor) *' + this.pagewidth * a + "px)"
									}
									if (children[i].style.top.includes("%")) {
										let a = parseFloat(children[i].style.top.split("%")[0]) / 100
										children[i].style.top = 'calc(var(--scale-factor) *' + this.pageheight * a + "px)"
									}
									dir[0].top = children[i].style.top
									dir[0].left = parseFloat(children[i].style.left.split("*")[1].split("px")[0])
									dir[0].innerText = children[i].innerText
									dir[0].fontSize = parseFloat(children[i].style.fontSize.split("*")[1].split("px")[0])
								}
							} else {
								if (children[i].innerHTML !== "") {
									let dirspan = children[i].getElementsByTagName("span")
									if (dirspan.length > 0) {
										for (let j = 0; j < dirspan.length; j++) {
											if (dirspan[j].TagName !== "BR") {
												if (dirspan[j].style.left.includes("%")) {
													dirspan[j].style.left = this.percenttopx(dirspan[j].style.left, this.pagewidth)
												}
												if (dirspan[j].style.top.includes("%")) {
													dirspan[j].style.top = this.percenttopx(dirspan[j].style.top, this.pageheight)
												}
												let issame = false
												dir.map(item => {
													if (item.top === dirspan[j].style.top) {
														item.innerText += dirspan[j].innerText
														item.left = item.left < parseFloat(dirspan[j].style.left.split("*")[1].split("px")[0]) ? item.left : parseFloat(dirspan[j].style.left.split("*")[1].split("px")[0])
														item.fontSize = item.fontSize > parseFloat(dirspan[j].style.fontSize.split("*")[1].split("px")[0]) ? item.fontSize : parseFloat(dirspan[j].style.fontSize.split("*")[1].split("px")[0])
														issame = true
													}
												})
												if (issame) {
													continue
												} else {
													dir.push({ top: dirspan[j].style.top, left: parseFloat(dirspan[j].style.left.split("*")[1].split("px")[0]), fontSize: parseFloat(dirspan[j].style.fontSize.split("*")[1].split("px")[0]), innerText: dirspan[j].innerText })
												}
											}
										}
									}
								} else {
									continue
								}
							}
							if (!dir[0].top) {
								dir.shift()
							}
							for (let k = 0; k < dir.length; k++) {
								let isin = false
								for (let j = 0; j < marklist.length; j++) {
									if (marklist[j].top === dir[k].top) {
										marklist[j].innerText += dir[k].innerText
										marklist[j].left = marklist[j].left < dir[k].left ? marklist[j].left : dir[k].left
										marklist[j].fontSize = marklist[j].fontSize < dir[k].fontSize ? marklist[j].fontSize : dir[k].fontSize
										isin = true
										break
									}
								}
								if (!isin) {
									marklist.push(dir[k])
								}
							}
						}
					}
					console.log(marklist);
					marklist.map((item, index) => {
						if (index === 0) {
							if (e.target.style.left.includes("%")) {
								e.target.style.left = this.percenttopx(e.target.style.left, this.pagewidth)
							}
							if (e.target.style.top.includes("%")) {
								e.target.style.top = this.percenttopx(e.target.style.top, this.pageheight)
							}
							if (parseFloat(e.target.style.top.split("*")[1].split("px")[0]) > parseFloat(this.y.split("*")[1].split("px")[0])) {
								item.left = this.x2 - 10 + "px"
							} else if (parseFloat(e.target.style.top.split("*")[1].split("px")[0]) === parseFloat(this.y.split("*")[1].split("px")[0])) {
								item.left = this.x2 < e.clientX ? this.x2 - 9 + "px" : e.clientX - 9 + "px"
							}
							else {
								item.left = e.clientX - 10 + "px"
							}
						} else {
							item.left = "calc(var(--scale-factor)*" + item.left + "px)"
						}
						item.fontSize = "calc(var(--scale-factor)*" + item.fontSize + "px)"
					})
					if (ispage) {
						return
					}
					marklist.forEach((item) => {
						//item.innerText = item.innerText.split(" ").join("")
						const regex = /[0-9.]/g;
						const regex2 = /\s/g;
						const regex3 = /[()"“”']/g;
						const matches = item.innerText.match(regex);
						const matches2 = item.innerText.match(regex2);
						const matches3 = item.innerText.match(regex3);
						const count = matches ? matches.length : 0;
						const count2 = matches2 ? matches2.length : 0;
						const count3 = matches3 ? matches3.length : 0;

						item.width = "calc(var(--scale-factor)*" + (parseFloat(item.fontSize.split("*")[1].split("px")[0]) * (item.innerText.length - count / 2 - (count2) * 3 / 4 - count3 * 5 / 8)) + "px)"
						item.height = "calc(var(--scale-factor)*" + (parseFloat(item.fontSize.split("*")[1].split("px")[0]) + 1) + "px)"
					})
					let id = this.parentpage(e.target) + "-" + Date.now()
					if (this.mode === 1) {
						this.drawline(this.parentpage(e.target), marklist, id, this.mode, null, null, null, 0)
					} else if (this.mode === 2) {
						this.popoverposition(e)
						this.etarget = e.target
						this.marklist = marklist
						this.id = id
						this.popbutton = true
						this.mouseover = true
						this.vis = true
					} else if (this.mode === 3) {
						this.popoverposition(e)
						this.etarget = e.target
						this.marklist = marklist
						this.id = id
						this.vis = true
					} else if (this.mode === 4) {
						this.popoverposition(e)
						this.etarget = e.target
						this.id = id
						this.vis = true
					}
				}, true)
			}
			this.loading = false
		},
		popoverposition(e) {
			const popover = this.$refs.popover;
			let timer = setTimeout(() => {
				const { clientX, clientY } = e;
				const { popperElm } = popover;
				let disX = clientX + this.$refs.a.offsetLeft + parseFloat(popperElm.style.width.split("px")) < this.$refs.a.offsetLeft + parseFloat(this.$refs.a.width)
					? clientX + this.$refs.a.offsetLeft
					: clientX + this.$refs.a.offsetLeft - 200
				let disY = clientY + this.$refs.a.offsetTop < 530 ? clientY + this.$refs.a.offsetTop : clientY + this.$refs.a.offsetTop - 180
				popover.popperElm.style.left = disX + "px";
				popover.popperElm.style.top = disY + "px";
				//popover.popperElm.style.height = "180px"
				clearTimeout(timer);
			}, 5);
		}
	}
}
</script>
<style scoped>
@import '/node_modules/pdfjs-dist/web/pdf_viewer.css';

.pdf-wrap {
	display: flex;
	flex-direction: column;
	align-items: center;
}

.canvas-container {
	border: 1px dashed #e1e1e1;
	position: relative;
	display: flex;
	flex-direction: column;
	justify-content: center;
}

/deep/.el-popover__title {
	border-bottom: 1px solid #e1e1e1;
	text-align: center;
	color: gray;
	padding-bottom: 4px;
	margin-bottom: 6px;
}

canvas {
	border: 1px dashed black;
	margin-bottom: 10px;
	height: 800px;
	overflow-y: scroll;
}

.el-tag+.el-tag {
	margin-left: 10px;
}

.button-new-tag {
	width: 80px;
	height: 32px;
	line-height: 30px;
	padding-top: 0;
	padding-bottom: 0;
}

.input-new-tag {
	width: 90px;
	margin-left: 10px;
	vertical-align: bottom;
}

.evidence {
	cursor: pointer;
}

.evidence:hover {
	color: blue;
}

.evidence:active {
	color: red;
}

.linkright {
	display: flex;
	height: 44px;
	margin-left: 8px;
	flex-direction: column;
	align-items: flex-start;
	justify-content: space-between;
}

.righttext {
	word-break: keep-all;
	white-space: nowrap;
	overflow: hidden;
	text-overflow: ellipsis;
}

.teachcard {
	text-align: left;
	width: 265px;
}

.teachcard2 {
	text-align: left;
	width: 220px;
}

.resultheader {
	padding: 10px;
}

.result {
	border: 2px solid rgb(36, 104, 240);
	border-radius: 5px;
	display: flex;
	flex-direction: column;
	justify-content: flex-start;
	align-items: flex-start;
	width: 160px;
	margin-top: 10px;
	cursor: pointer;
	background-color: rgb(209, 227, 250);
	padding: 8px;
}

/deep/.el-divider--horizontal {
	display: block;
	height: 1px;
	width: 160px;
	margin: 2px 0;
	background-color: rgb(0, 0, 0);
}

/deep/.el-card__body {
	padding: 8px;
}

/deep/.el-card__header {
	padding: 8px;
}
</style>
