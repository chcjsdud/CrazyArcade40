#pragma once
class MapGameObject
{
public:
	MapGameObject();
	~MapGameObject();


	MapGameObject(const MapGameObject& _Other) = delete;
	MapGameObject(MapGameObject&& _Other) noexcept = delete;
	MapGameObject& operator=(const MapGameObject& _Other) = delete;
	MapGameObject& operator=(MapGameObject&& _Other) noexcept = delete;
protected:

private:

};