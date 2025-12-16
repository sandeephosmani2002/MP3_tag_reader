# MP3_Tag_Reader_And_Editor
  <p class="meta">
    Terminal-based MP3 metadata reader and editor written in <strong>C</strong>. Reads and edits ID3v2 tags (targeting ID3v2.3.0).  
  </p>

  <h2>Project Highlights</h2>
  <ul class="features">
    <li>View MP3 metadata: <em>Title, Artist, Album, Year, Genre, Comments</em>.</li>
    <li>Edit specific metadata frames (creates a modified copy of the MP3 with the updated tag).</li>
    <li>Primary support for ID3v2.3.0; partial/limited support for earlier versions only (v2.4 excluded).</li>
    <li>Command-line interface for quick operations.</li>
    <li>Modular C implementation with separate source and header files for readability and reuse.</li>
  </ul>

  <h2>Supported Tag Frames (examples)</h2>
  <ul>
    <li><code>TIT2</code> — Title</li>
    <li><code>TPE1</code> — Artist</li>
    <li><code>TALB</code> — Album</li>
    <li><code>TYER</code> — Year</li>
    <li><code>TCON</code> — Genre</li>
    <li><code>COMM</code> — Comment</li>
  </ul>

  <h2>Project Structure</h2>
  <ul class="files">
    <li><strong>MP3_main.c</strong> # Main program logic (CLI handling, flow control)</li>
    <li><strong>MP3_view.c</strong> # Functions for reading MP3 tags </li>
    <li><strong>MP3_edit.c</strong> # Functions for editing MP3 tags</li>
    <li><strong>MP3_header.h</strong> # Header declarations</li>
    <li><strong>sample.mp3</strong> # Example test file
    <li><strong>README.md</strong> # This file .</li>
  </ul>

  <h2>Usage</h2>
  <p>View tags</p>
  <pre><code>./a.out -v &lt;filename.mp3&gt;</code></pre>
  <p>Edit a tag</p>
  <pre><code>./a.out -e  &lt;tag_option&gt; &lt;new_value&gt; &lt;filename.mp3&gt; </code></pre>
  <p>Tag options (as implemented):</p>
  <pre><code>-t  Title
-a  Artist
-A  Album
-y  Year
-c  Composer (uses COMM frame)
-g  Genre</code></pre>
  <p>Help menu</p>
  <pre><code>./a.out --h</code></pre>
  
  <h2>Example</h2>
  <p>Viewing tags</p>
  <pre><code>./a.out -v sample.mp3

----- MP3 TAGS -----
Title   :    Sunny Sunny - Yo Yo Honey Singh - [SongsPk.CC]
Artist  :    Yo Yo Honey Singh - [SongsPk.CC]
Album   :    Yaariyan
Year    :    2013
Genre   :    Bollywood Music - [SongsPk.CC]
Comment :    eng
</code></pre>

  <p>Editing title (example):</p>
  <pre><code>./a.out -e -t "New Song Title" sample.mp3

Select Edit Option
Select Title change option
Title : Kantara
Title changed successfully!
</code></pre>

  <h2>How it works (high-level)</h2>
  <ol>
    <li><strong>Header &amp; Version Check:</strong> The program checks the first 3 bytes for the "ID3" header, reads the two version bytes and only proceeds for ID3v2.3.0.</li>
    <li><strong>Frame scanning:</strong> The reader moves into the ID3 tag block and iterates over known frames (e.g., TIT2, TPE1, TALB, TYER, TCON, COMM) to extract the stored text. The reading routine fills fixed buffers (Title, Artist, Album, Year, etc.).</li>
    <li><strong>Editing:</strong> When updating a single frame, the program creates a temporary output file (<code>temp.mp3</code>), copies the ID3 header, and for each frame either writes the original content or writes the replaced value for the target frame. After a successful write, the original file is deleted and the temp file is renamed back to the original filename.</li>
    <li><strong>Endian handling:</strong> Frame sizes in ID3v2 are read and byte-swapped as required by the implementation before reading/writing.</li>
  </ol>

  <h2>Implementation notes &amp; limitations</h2>
  <ul>
    <li>Supports and expects <strong>ID3v2.3.0</strong>. Attempting to edit unsupported versions will be rejected by the version check.</li>
    <li>Frame-handling loop is implemented for a fixed number of frames in the provided code (reads up to 6 frames). If tags are arranged differently or additional frames are present, you may need to extend parsing logic.</li>
    <li>The current code uses fixed-size buffers for tag contents (e.g., 50–100 bytes). Very long tag values may be truncated; consider dynamic allocation for robust handling of large values.</li>
    <li>Text encoding: the code assumes simple ASCII/ISO-8859-1 textual frames. For full Unicode (UTF-16/UTF-8) support, the frame encoding byte must be checked and converted properly.</li>
    <li>Backup: The editor overwrites the original file after creating <code>temp.mp3</code>. Keep backups of original files when testing.</li>
  </ul>

  <h2>Troubleshooting</h2>
  <ul>
    <li><strong>File not opening:</strong> Ensure the MP3 exists and you have read/write permissions.</li>
    <li><strong>Unsupported ID3 version:</strong> The program explicitly checks and reports unsupported versions (only v2.3 allowed).</li>
    <li><strong>Incorrect command usage:</strong> Run with no args or <code>--help</code> to show usage: the help text is printed from <code>MP3_main.c</code>.</li>
  </ul>

  <h2>Contributing</h2>
  <p>To improve this tool, consider:</p>
  <ul>
    <li>Adding proper UTF-16/UTF-8 handling for ID3 text frames.</li>
    <li>Parsing the entire tag header size properly and iterating until end-of-tag rather than a fixed frame count.</li>
    <li>Replacing fixed buffers with safe dynamic allocations and boundary checks.</li>
    <li>Adding unit tests for parsing/writing frames.</li>

  </ul>
