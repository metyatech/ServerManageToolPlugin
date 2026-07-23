// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerProcess.h"

DEFINE_LOG_CATEGORY_STATIC(LogServerProcess, Log, All);

ServerProcess::ServerProcess(const FString& MapName, int32 Port)
	: RequestedPort(Port) {
	// UnrealEditor.exe のパスを取得
	FString EditorPath = FPlatformProcess::ExecutablePath();

	// 現在開いているプロジェクトのパスを取得
	FString ProjectFilePath = FPaths::GetProjectFilePath();

	if (!FPaths::FileExists(EditorPath)) {
		UE_LOG(LogServerProcess, Error,
		       TEXT("SMT_SERVER_PROCESS_LAUNCH_FAILED map=%s requested_port=%d executable=%s project=%s reason=editor_not_found"),
		       *MapName, RequestedPort, *EditorPath, *ProjectFilePath);
		return;
	}

	if (!FPaths::FileExists(ProjectFilePath)) {
		UE_LOG(LogServerProcess, Error,
		       TEXT("SMT_SERVER_PROCESS_LAUNCH_FAILED map=%s requested_port=%d executable=%s project=%s reason=project_not_found"),
		       *MapName, RequestedPort, *EditorPath, *ProjectFilePath);
		return;
	}

	// コマンドライン引数を作成
	FString CommandLineArgs =
	    FString::Printf(TEXT("\"%s\" %s -Port=%d -ServerManageExpectedPort=%d -server -log"),
	                    *ProjectFilePath, *MapName, RequestedPort, RequestedPort);

	// プロセスを起動
	ProcessHandle =
	    FPlatformProcess::CreateProc(*EditorPath, *CommandLineArgs, true, false,
	                                 false, nullptr, 0, nullptr, nullptr);

	if (!ProcessHandle.IsValid()) {
		UE_LOG(LogServerProcess, Error,
		       TEXT("SMT_SERVER_PROCESS_LAUNCH_FAILED map=%s requested_port=%d executable=%s project=%s reason=create_proc_failed"),
		       *MapName, RequestedPort, *EditorPath, *ProjectFilePath);
		return;
	}

	UE_LOG(LogServerProcess, Log, TEXT("Local server process started: %s %s"),
	       *EditorPath, *CommandLineArgs);
}

void ServerProcess::Kill() {
	if (ProcessHandle.IsValid()) {
		FPlatformProcess::TerminateProc(ProcessHandle);
		FPlatformProcess::CloseProc(ProcessHandle);
		ProcessHandle.Reset();
		UE_LOG(LogServerProcess, Log, TEXT("Local server process stopped"));
	}
}

bool ServerProcess::IsValid() const {
	return ProcessHandle.IsValid();
}

int32 ServerProcess::GetRequestedPort() const {
	return RequestedPort;
}

ServerProcess::~ServerProcess() {
	Kill();
}
