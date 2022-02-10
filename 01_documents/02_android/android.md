# android to navigation
官方文档：https://developer.android.google.cn

## 1.tutorial

### 1.1. 接入点和适应性
- andoroid应用提供：
  - 多个入口点（activities，窗口）
  - 适配不同类型的设备（不同窗口大小，分辨率）

### 1.2. app构建

#### 1.2.1. 新建工程

- **安装**[Android Studio](https://developer.android.google.cn/studio/)
- **Create New Project**
- **Empty Activity**
  - **project** name
  - **package** name
  - folder
  - **language**
  - mininum sdk
- **Project files**
  - **app**
    - **java**
      - **com.example.myfirstapp** `应用入口`
        - **MainActivity**
    - **res**
      - **layout** `UI布局`
        - **activity_main.xml**
    - **manifests**
      - **AndroidManifest.xml** `清单文件`
    - **Gradle Scripts**
      - **build.gradle** `配置build`
        - 项目    **Project**: name
        - 应用模块    **Moudle**: name.app（one/per moudle）

#### 1.2.2. 新建界面

- **界面**（层次）**结构**
  - ViewGroup 【layout的对象：容器】
    - view 【widget的对象：按钮/文本框】
- **布局**（layout）**编辑**
  - **Select Design Surface**
    - Blueprint
  - **View Options**
    - Show All Constraints
  - **Enable Autoconnection to Parent**
    - close
  - **Default Margins**（view的外边距）
    - 0 -> 16
  - **Device for Preview**
    - ex. -> **5.5, 1440 × 2560, 560 dpi (Pixel XL)**
  - **Component Tree**（layout的视图层次结构）
    - 根视图：ConstraintLayout

### 1.3. app调试

- 问题-1

```kotlin
Failed to install the following Android SDK packages as some licences have not been accepted.
   build-tools;30.0.2 Android SDK Build-Tools 30.0.2
To build this project, accept the SDK license agreements and install the missing components using the Android Studio SDK Manager.
Alternatively, to transfer the license agreements from one workstation to another, see http://d.android.com/r/studio-ui/export-licenses.html
```

- 解决-1

```powershell
$cd sdk/tools/bin
$./sdkmanager --update
$./sdkmanager --licenses
```

