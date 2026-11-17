fetch('/header.html')
  .then(r => r.text())
  .then(html => {
    document.getElementById('menu-placeholder').innerHTML = html;
    const norm = p => p.replace(/\.html$/, '').replace(/\/$/, '') || '/';
    const mostani = norm(location.pathname);
    document.querySelectorAll('#menu-placeholder a').forEach(a => {
      if (norm(new URL(a.href).pathname) === mostani) {
        a.classList.add('w3-light-grey', 'w3-text-green');
        a.style.fontWeight = 'bold';
      }
    });
  });