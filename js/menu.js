// 26.11.22 Google AI Studio
"use strict";

(() => {
  const menuFetch = fetch('/header.html').then(r => {
    if (!r.ok) throw new Error(`HTTP ${r.status}`);
    return r.text();
  });

  const domReady = document.readyState === 'loading'
    ? new Promise(r => document.addEventListener('DOMContentLoaded', r, { once: true }))
    : Promise.resolve();

  Promise.all([menuFetch, domReady])
    .then(([html]) => {
      const placeholder = document.getElementById('menu-placeholder');
      if (!placeholder) return;
      placeholder.innerHTML = html;

      const norm = p => p.replace(/(\/index)?(\.html)?$/, '').replace(/\/$/, '') || '/';
      const mostani = norm(location.pathname);

      for (const a of placeholder.querySelectorAll('a')) {
        if (norm(a.pathname) === mostani) {
          a.classList.add('w3-light-grey', 'w3-text-green');
          a.style.fontWeight = 'bold';
          a.setAttribute('aria-current', 'page');
        }
      }
    })
    .catch(err => console.error('Menü betöltési hiba:', err));
})();