import http.server
import socketserver
import threading
import webbrowser
import os
import sys

PORT = 8000
HTML_FILE = "image_preview.html"
IMAGE_EXT = ".jpg"      # 想换格式改这里
FILENAME_FORMAT = ""     # 文件名必须包含这个字符串，空字符串代表不过滤

HTML_CONTENT = f"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8" />
<title>Image Preview ({IMAGE_EXT})</title>
<style>
  body{{font-family:sans-serif;margin:0;padding:0;background:#fafafa}}
  h1{{text-align:center;padding:12px;background:#222;color:#fff;margin:0}}
  img{{width:100%;display:block;margin:0;border-bottom:1px solid #ccc}}
  #image-container{{padding-bottom:50px}}
  #reload-btn{{display:block;margin:10px auto;padding:6px 12px;font-size:16px;cursor:pointer}}
</style>
</head>
<body>
<h1>Image Preview ({IMAGE_EXT})</h1>
<button id="reload-btn">Reload Images</button>
<div id="image-container">Loading...</div>
<script>
  const IMAGE_EXT = "{IMAGE_EXT}";
  const FILENAME_FORMAT = "{FILENAME_FORMAT}";
  async function loadImages(){{
    const container=document.getElementById('image-container');
    container.innerHTML='';
    try{{
      const res=await fetch(`./?v=${{Date.now()}}`,{{cache:'no-store'}});
      const text=await res.text();
      const doc=new DOMParser().parseFromString(text,'text/html');
      const links=Array.from(doc.querySelectorAll('a'))
        .map(a=>a.getAttribute('href'))
        .filter(h => h.toLowerCase().endsWith(IMAGE_EXT) && h.includes(FILENAME_FORMAT))
        .sort();
      if(links.length===0){{container.textContent='No images found';return;}}
      links.forEach(h=>{{
        const img=document.createElement('img');
        img.src=`${{h}}?v=${{Math.random()}}`;
        img.alt=h;
        container.appendChild(img);
      }});
    }}catch{{
      container.textContent='Load error. Use a local server.';
    }}
  }}
  document.getElementById('reload-btn').addEventListener('click',loadImages);
  loadImages();
</script>
</body>
</html>
"""

def write_html(path):
    with open(path, "w", encoding="utf-8") as f:
        f.write(HTML_CONTENT)

def start_server(directory):
    os.chdir(directory)
    Handler = http.server.SimpleHTTPRequestHandler
    with socketserver.TCPServer(("", PORT), Handler) as httpd:
        print(f"Serving at http://localhost:{PORT}/")
        httpd.serve_forever()

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(sys.argv[0]))
    html_path = os.path.join(script_dir, HTML_FILE)
    write_html(html_path)
    threading.Thread(target=start_server, args=(script_dir,), daemon=True).start()
    webbrowser.open(f"http://localhost:{PORT}/{HTML_FILE}")
    print("Press Ctrl+C to stop the server.")
    try:
        while True:
            pass
    except KeyboardInterrupt:
        print("\nServer stopped.")
