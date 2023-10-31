<template>
  <div v-loading="loading" element-loading-text="拼命加载中">
    <a @click="go">asd</a>{{ currentPage }}
    <iframe ref="a" src="/pdfjs/web/viewer.html?file=http://120.55.63.197:3000/images/1.pdf" width="830"
      height="650"></iframe>
  </div>
</template>
<script>
export default {
  data() {
    return {
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
      markpage:[]
    }
  },
  watch: {
    currentPage: {
      deep: true,
      handler() { 
        setTimeout(() => {
          console.log(this.markpage,this.getTextLayer());
        }, 500);
      }
    }
  },
  mounted() {
    this.doc = this.$refs.a
    this.docselection = this.doc.contentWindow
    setTimeout(() => {
      this.choose()
      this.getTextLayer()
      //console.log(this.markpage);
    }, 3000)
  },
  methods: {
    getTextLayer() {
      let newmarkpage = []
      let newdrawpage=[]
      let a = this.doc.contentDocument.getElementsByClassName("textLayer")
      for (let i = 0; i < a.length; i++) {
        if (!this.markpage.includes(a[i].parentNode.getAttribute("data-page-number"))) {
          newdrawpage.push(a[i].parentNode.getAttribute("data-page-number"))
        }
        newmarkpage.push(a[i].parentNode.getAttribute("data-page-number"))
      }
      this.markpage=newmarkpage
      return newdrawpage
    },
    go() {
      //let a = e.target
      let b = document.createElement("a")
      b.setAttribute("href", "#page1")
      console.log(this.$refs.a.contentWindow);
      this.$refs.a.contentDocument.getElementById("viewerContainer").appendChild(b);
      //b.click()
      b.remove()
    },
    drawline(page, shape) {
      const parent = this.doc.contentDocument.querySelectorAll("div[data-page-number='" + page + "'].page")[0];
      //console.log(parent);
      shape.forEach(item => {
        let newdiv = document.createElement("div")
        newdiv.style.position = "absolute"
        newdiv.style.zIndex = "1"
        newdiv.style.borderRadius = "2px"
        newdiv.style.backgroundColor = "rgba(235,73,73,0.8)"
        newdiv.style.width = item.width
        newdiv.style.height = item.height
        newdiv.style.top = item.top
        newdiv.style.left = item.left
        newdiv.setAttribute("id",item.id)
        if (item.width.match(/\d+/g).map(Number)[0] + item.left.match(/\d+/g).map(Number)[0] < 793.6) {
          console.log(newdiv);
          parent.appendChild(newdiv)
        }
      })
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
      sel.getElementById("viewerContainer").addEventListener("scroll", () => {
        let pdfInfo = this.docselection.PDFViewerApplication;
        if (pdfInfo.page !== this.currentPage) {
          this.currentPage = pdfInfo.page
        }
      })
      for (let i = 0; i < sel.getElementsByClassName('page').length; i++) {
        sel.getElementsByClassName("page")[i].setAttribute("id", "page" + sel.getElementsByClassName("page")[i].getAttribute("data-page-number"))
        sel.getElementsByClassName('page')[i].addEventListener("mousedown", (e) => {
          if (!e.target.style.left) {
            return
          }
          this.x = parseFloat(e.target.style.left.split("*")[1].split("px")[0])
          this.width = e.target.style.left.split("*")[0] + "*"
          this.y = e.target.style.top
          this.x2 = e.clientX
        }, true)
      }
      for (let i = 0; i < sel.getElementsByClassName('page').length; i++) {
        sel.getElementsByClassName('page')[i].addEventListener("mouseup", (e) => {
          if (this.x2 === e.clientX || this.docselection.getSelection().getRangeAt(0).toString() === "") {
            return
          }
          if (this.docselection.getSelection().getRangeAt(0).cloneContents().childNodes[0].nodeName === '#text') {
            let shape = []
            let childline = { top: "", left: "", width: "", height: "" }
            childline.id = this.parentpage(e.target)+"-"+Date.now()+"1"
            childline.height = e.target.style.fontSize
            childline.top = this.y
            //console.log(typeof e.clientX, e.clientX, typeof this.x2, this.x2);
            if (this.x2 < e.clientX) {
              childline.left = this.x2 - 10 + "px"
              childline.width = e.clientX - this.x2 + "px"
            } else {
              childline.left = e.clientX - 10 + "px"
              childline.width = this.x2 - e.clientX + "px"
            }
            shape.push(childline)
            //this.parentpage(e.target).appendChild(a)
            this.drawline(this.parentpage(e.target), shape)
            return
          }
          let ispage = false
          let children = this.docselection.getSelection().getRangeAt(0).cloneContents().childNodes
          let marklist = []
          for (let i = 0; i < children.length; i++) {
            if (children[i].className === "page" || children[i].className === "textLayer") {
              ispage = true
              this.$message({ message: "不允许跨段标注", type: "warning" })
              break
            } else {
              let dir = [{ top: "", left: 999999, innerText: "", fontSize: 0 }]
              if (children[i].className === "") {
                console.log(children[i]);
                if (children[i].innerHTML !== "") {
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
          marklist.map((item, index) => {
            if (index === 0) {
              if (parseFloat(e.target.style.top.split("*")[1].split("px")[0]) >= parseFloat(this.y.split("*")[1].split("px")[0])) {
                item.left = this.x2 - 13 + "px"
              } else {
                item.left = e.clientX - 13 + "px"
              }
            } else {
              item.left = "calc(var(--scale-factor)*" + item.left + "px)"
            }
            item.fontSize = "calc(var(--scale-factor)*" + item.fontSize + "px)"
          })
          if (ispage) {
            return
          }
          marklist.forEach((item,index) => {
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
            item.id=this.parentpage(e.target)+"-"+Date.now()+"-"+index
            item.width = "calc(var(--scale-factor)*" + (parseFloat(item.fontSize.split("*")[1].split("px")[0]) * (item.innerText.length - count / 2 - (count2) * 3 / 4 - count3 * 5 / 8)) + "px)"
            item.height = "calc(var(--scale-factor)*" + (parseFloat(item.fontSize.split("*")[1].split("px")[0]) + 1) + "px)"
            /*let a = document.createElement("div")
            a.style.position = "absolute"
            a.style.zIndex = "1"
            a.style.backgroundColor = "red"
            a.style.top = item.top
            a.style.left = item.left
            a.style.width = "calc(var(--scale-factor)*" + (parseFloat(item.fontSize.split("*")[1].split("px")[0]) * (item.innerText.length)) + "px)"
            a.style.height = "calc(var(--scale-factor)*" + (parseFloat(item.fontSize.split("*")[1].split("px")[0]) + 1) + "px)"
            a.setAttribute("id", Date.now() + "")*/
            /*if ((parseFloat(item.fontSize.split("*")[1].split("px")[0]) * item.innerText.length) + a.style.left.match(/\d+/g).map(Number)[0] < 793.6) {
              this.parentpage(e.target).appendChild(a)
            }*/
          })
          this.drawline(this.parentpage(e.target), marklist)
        }, true)
      }
      this.loading = false
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

canvas {
  border: 1px dashed black;
  margin-bottom: 10px;
  height: 800px;
  overflow-y: scroll;
}
</style>
