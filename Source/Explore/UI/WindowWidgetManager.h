#pragma once

#include "WindowEnum.h"

/**
 * @brief 窗口管理单例类
 */
class FWindowWidgetManager
{
private:
	/**
	 * @brief 私有构造函数
	 */
	FWindowWidgetManager();
	
public:
	/**
	 * @brief 析构函数
	 */
	~FWindowWidgetManager();
	
	/**
	 * @brief 获取单例
	 * @return 单例
	 */
	static FWindowWidgetManager* GetInstance();

	/**
	 * @brief 初始化
	 * @param World World
	 */
	void Initialize(class UWorld* World);

	/**
	 * @brief 打开窗口
	 * @param ID 窗口ID
	 * @return 打开的窗口
	 */
	class UWindowWidget* OpenWindow(EWindowWidgetID ID);

	/**
	 * @brief 打开窗口
	 * @tparam T 窗口类型
	 * @param ID 窗口ID
	 * @return 打开的窗口
	 */
	template <typename T>
	T* OpenWindow(EWindowWidgetID ID)
	{
		return Cast<T>(OpenWindow(ID));
	}

	/**
	 * @brief 关闭窗口
	 * @param ID 要关闭的窗口
	 */
	void CloseWindow(EWindowWidgetID ID);

	/**
	 * @brief 获取打开的窗口
	 * @param ID 窗口ID
	 * @return 打开的窗口
	 */
	class UWindowWidget* GetWindow(EWindowWidgetID ID) const;
	
	/**
	 * @brief 获取打开的窗口
	 * @tparam T 窗口类型
	 * @param ID 窗口ID
	 * @return 打开的窗口
	 */
	template <typename T>
	T* GetWindow(EWindowWidgetID ID) const
	{
		return Cast<T>(GetWindow(ID));
	}

	/**
	 * @brief 窗口是否打开
	 * @param ID 窗口ID
	 * @return 是否打开
	 */
	bool IsWindowOpened(EWindowWidgetID ID) const;

	/**
	 * @brief 播放伤害数字
	 * @param DamageValue 伤害数字
	 * @param WorldPosition 世界坐标
	 */
	void PlayDamagePopup(int DamageValue, const FVector& WorldPosition);

	/**
	 * @brief 获取窗口Owner
	 */
	FORCEINLINE UWorld* GetWindowOwner() const
	{
		return WindowOwner;
	}

private:
	/**
	 * @brief 设置是否启用游戏输入
	 * @param bEnabled 是否启用
	 */
	void SetGameInputEnabled(bool bEnabled);

private:
	/**
	 * @brief 窗口拥有者
	 */
	UWorld* WindowOwner = nullptr;
	
	/**
	 * @brief 所有显示的窗口列表
	 */
	TArray<UWindowWidget*> Windows;

	/**
	 * @brief 伤害数字
	 */
	UClass* DamagePopupClass = nullptr;

	/**
	 * @brief 游戏输入是否有效
	 */
	bool bGameInputEnabled = true;
};
