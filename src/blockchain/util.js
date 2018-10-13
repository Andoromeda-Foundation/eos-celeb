export function escapeHtml (unsafe) {
  return unsafe
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;')
    .replace(/'/g, '&#039;')
}

export function padTimeZero (str) {
  let t = '00' + str
  return t.slice(t.length - 2, t.length)
}

export function formatCountdown (remaining) {
  const seconds = remaining % 60
  remaining = ~~(remaining / 60)
  const minutes = remaining % 60
  remaining = ~~(remaining / 60)
  const hours = remaining
  return `${padTimeZero(hours)}:${padTimeZero(minutes)}:${padTimeZero(seconds)}`
}
