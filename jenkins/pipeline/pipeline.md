## pipe语法

### 基本规则

- 基本语句和表达式遵循与Groovy语法相同的规则 ，但有以下例外：
  - Pipeline的顶层必须是块，具体来说是：pipeline { }
  - 没有分号作为语句分隔符。每个声明必须在自己的一行
  - 块只能包含Sections, Directives, Steps或赋值语句。
  - 属性引用语句被视为无参方法调用。所以例如，输入被视为input（）

### 整体组成

- pipeline
  - pipeline { Pipeline代码}
- node
  - 节点，执行代码的机器
- stage
  - 关键字stage，就是一段代码块，一般个stage包含一个业务场景的自动化，例如：
    - build是一个stage
    - test是第二个stage
    - deploy是第三个stage
    - 通过stage隔离，让Pipeline代码读写非常直观。一个stages包含多个stage(单独一个可以省略)。
- step
  - 关键字step就是一个简单步骤，一般就是几行代码或者调用外部一个模块类的具体功能。step写在stage的大括号里。一个steps包含多个step(单独一个可以省略)。

### [具体语法](https://blog.csdn.net/weixin_41988331/article/details/81672128?spm=1001.2014.3001.5502)

#### 1. agent

- agent部分指定整个Pipeline或特定阶段将在Jenkins环境中**执行位置**
- agent 部分的放置位置：
  - 必须在pipeline块内的顶层定义 
  - stage级使用可选

- 参数
  - **any**
    - 在任何可用的agent 上执行Pipeline或stage
  - none
    - 当在pipeline块的顶层使用none时，将不会为整个Pipeline运行分配全局agent ，每个stage部分将需要包含其自己的agent部分。
  - label
    - 使用提供的label标签，在Jenkins环境中可用的代理上执行Pipeline或stage。例如：agent { label 'my-defined-label' }
  - node
    - agent { node { label 'labelName' } }，等同于 agent { label 'labelName' }，但node允许其他选项（如customWorkspace）。
  - docker
    - 定义此参数时，执行Pipeline或stage时会动态供应一个docker节点去接受Docker-based的Pipelines。 
    - docker还可以接受一个args，直接传递给docker run调用。例如：agent { docker 'maven:3-alpine' }或

