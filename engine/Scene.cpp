#include "Scene.h"
#include "GameApp.h"   // 用 GameApp 的成员函数，必须见到完整定义（前置声明只能存指针）

// 场景请求切换：场景自己不做主，把"申请"转交给引擎
// （引擎不会当场就换——它记下来，等这一帧走完再动手，不然场景在自己函数里被删掉就炸了）
void Scene::requestSceneChange(SceneType newScene) {
    if (app_) app_->requestSceneChange(newScene);   // 转交给引擎（还没接线就不吭声）
}
