# NVDShowWrap.vss
Northern Verse ([@Project9k](https://twitter.com/project9k))氏作のuLilithで使われているVSSプラグイン`NVDShow.vss`を、様々なメタデータが読み込めるように改良したものです。

m4aなど、エクスプローラーで表示できるものには多分対応していると思います。

## 動作確認環境
- Windows 10 Pro version 1809 (October 2018 Update) x64
- uLilith 1.0.0 (2019/01/01) (x64)

※x86版は試してません。

## インストール
1. [Project9k氏のTwitter](https://twitter.com/project9k)からuLilithをインストールします。
2. uLilithを起動してタグを表示したいファイルが`DirectShowFilter`で再生されることを確認します。
3. uLilithを終了します。
4. `NVDShowWrap.vss`を`Plugin`フォルダに置きます。
5. `NVDShow.vss`のファイル名を`NVDShow.vss.org`に変更します。
   - このファイル名で使用するので削除しないでください。
6. uLilithを起動して該当のファイルのタグが表示されることを確認します。

## 注意事項
- このVSSプラグインは無保証です。
- 元の`DirectShowFilter`はファイル情報からフィルタの設定に飛べましたが`NVDShowWrap.vss`では未実装です。

## ビルド
### 環境
- Windows 10 Pro version 1809 (October 2018 Update) x64
- Visual Studio Community 2019

### 依存関係
- uLilithの`SDK\VSS`フォルダにある`uLilithPluginSDK`
  - includeされそうな位置に解凍してください。
  - ビルドして`NVLibCore.lib`と`NVAFLib.lib`を生成してください。
- Windows SDK
  - 10.0.18362.0を使いましたがもっと前でもいいかも

### 方法
1. Visual Studioで開いてビルドする。

## ライセンス
このプロジェクトはMITライセンスでリリースしています。