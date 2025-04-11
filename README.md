<h1>gtk-3-no-portal-cheat</h1>
<div>make gtk 3 not use <a href="https://wiki.archlinux.org/title/XDG_Desktop_Portal?useskin=vector">portals</a> for dialogs</div>
<table>
<tr><th>before</th><th>after</th></tr>
<tr><td><img src="before.png"></td><td><img src="after.png"></td></tr>
</table>
<h2>how to use</h2>
<div>I have <code>gtk-3-no-portal-cheat.so</code> in <code>/home/asd/a</code> folder and I want <code>org.gimp.GIMP.Nightly</code> flatpak to not use portals.</div>
<hr>
<div>if you want <i>gtk-3-no-portal-cheat</i> by default:</div>
<ul><li>run<pre>flatpak override --user --filesystem=/home/asd/a/gtk-3-no-portal-cheat.so:ro --env=LD_AUDIT=/home/asd/a/gtk-3-no-portal-cheat.so org.gimp.GIMP.Nightly</pre></li></ul>
<div>if you don't want <i>gtk-3-no-portal-cheat</i>:</div>
<ul><li>(this resets all <code>org.gimp.GIMP.Nightly</code> flatpak overrides if they exist, for granular override editing use <a href="https://flathub.org/apps/com.github.tchx84.Flatseal"><i>flatseal</i></a>)<br>run<pre>flatpak override --user --reset org.gimp.GIMP.Nightly</pre></li></ul>
<div>if you want <i>gtk-3-no-portal-cheat</i> once:</div>
<ul><li>run<pre>flatpak run --filesystem=/home/asd/a/gtk-3-no-portal-cheat.so:ro --env=LD_AUDIT=/home/asd/a/gtk-3-no-portal-cheat.so org.gimp.GIMP.Nightly</pre></li></ul>
<h2>how to compile</h2>
<div>I have repository files in <code>/home/asd/a</code> folder.</div>
<ol>
<li>install <a href="https://flathub.org/apps/org.freedesktop.Sdk"><code>org.freedesktop.Sdk</code> flatpak</a></li>
<li>run<pre>flatpak run --filesystem=/home/asd/a --cwd=/home/asd/a org.freedesktop.Sdk build.sh</pre>(this creates <code>/home/asd/a/gtk-3-no-portal-cheat.so</code> file)</li>
</ol>
