"use client"

import { useCallback } from "react"

type NotificationVariant = "success" | "info" | "error"

export const useNotification = () => {
  const showNotification = useCallback(
    (variant: NotificationVariant, title: string, message?: string, duration?: number) => {
      if (typeof window !== "undefined" && (window as any).showNotification) {
        return (window as any).showNotification(variant, title, message, duration)
      }
    },
    [],
  )

  return {
    success: (title: string, message?: string) => showNotification("success", title, message, 4000),
    info: (title: string, message?: string) => showNotification("info", title, message, 4000),
    error: (title: string, message?: string) => showNotification("error", title, message, 4000),
  }
}
