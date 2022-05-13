#pragma once
#include <GameEngine\GameEngineActor.h>
#include <string>
#include <vector>

class VideoPlayer : public GameEngineActor
{
public:
    VideoPlayer();
    ~VideoPlayer();

    VideoPlayer(const VideoPlayer& _Other) = delete;
    VideoPlayer(VideoPlayer&& _Other) noexcept = delete;
    VideoPlayer& operator=(const VideoPlayer& _Other) = delete;
    VideoPlayer& operator=(VideoPlayer&& _Other) noexcept = delete;

private:
    std::string Name_;
    int StartFrame_;
    int EndFrame_;
    float Interval_;
    float Time_;
    float ElapsedTime_;
    bool VideoFinished_;
    std::vector<GameEngineRenderer*> VideoFrameRenderers_;

public:
    void SetInfo(std::string _Name, int _StartFrame, int _EndFrame, float _Time);

    bool IsVideoFinished() { return VideoFinished_; }

protected:
    virtual void Start() override;
    virtual void Render() override;
    virtual void Update() override;
};

