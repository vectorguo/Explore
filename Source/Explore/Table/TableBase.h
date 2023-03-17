// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

template <typename T>
class EXPLORE_API FTableBase
{
	FTableBase() {}

public:
	virtual ~FTableBase() {}

	/**
	 * @brief 初始化
	 */
	static void Initialize(const TCHAR* Name)
	{
		Destroy();

		Instance = new FTableBase();

		auto DataTable = LoadObject<UDataTable>(nullptr, Name);
		if (DataTable)
		{
			auto RowNames = DataTable->GetRowNames();
			for (const auto& RowName : RowNames)
			{
				FString ContextString;
				auto* RowData = DataTable->FindRow<T>(RowName, ContextString);
				if (RowData)
				{
					Instance->Rows.Emplace(RowData->ID, RowData);
				}
			}
		}
	}

	/**
	 * @brief 销毁
	 */
	static void Destroy()
	{
		if (Instance)
		{
			Instance->Rows.Empty();
			delete Instance;
			Instance = nullptr;
		}
	}
	
	/**
	 * @brief 获取ID对应的行数据
	 * @param ID ID
	 * @return 配置表对应行数据
	 */
	static const T* GetRow(int32 ID)
	{
		if (Instance)
		{
			const auto* Row = Instance->Rows.Find(ID);
			return Row == nullptr ? nullptr : *Row;
		}
		return nullptr;
	}

	/**
	 * @brief 获取所有行数据
	 * @return 所有行数据
	 */
	static const TMap<int32, T*>* GetRows()
	{
		return Instance ? &Instance->Rows : nullptr;
	}

	/**
	 * @brief 检查ID是否有效
	 * @param ID 表ID
	 * @return ID是否有效
	 */
	static bool IsValid(int32 ID)
	{
		return Instance == nullptr ? false : Instance->Rows.Contains(ID);
	}

private:
	/**
	 * @brief 单例
	 */
	static FTableBase* Instance;
	
	/**
	 * @brief 数据行Map
	 */
	TMap<int32, T*> Rows;
};

//静态成员初始化
template <typename T>
FTableBase<T>* FTableBase<T>::Instance = nullptr;