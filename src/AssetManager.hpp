#pragma once


#include <map>
#include <memory>
#include <string>

template <typename T>
class AssetManager
{
public:
	std::shared_ptr<T> getAsset(const std::string& id);
	void setAsset(const std::string& id, const std::string& path);
private:
	std::map<std::string, std::shared_ptr<T>> m_assets;
};

template <typename T>
std::shared_ptr<T> AssetManager<T>::getAsset(const std::string& id)
{
	auto it = m_assets.find(id);
	if (it == m_assets.end())
		return nullptr;
	return it->second;
}

template <typename T>
void AssetManager<T>::setAsset(const std::string& id, const std::string& path)
{
	std::unique_ptr<T> asset = std::make_unique<T>();
	asset->loadFromFile(path);
	m_assets.emplace(id, std::move(asset));
}