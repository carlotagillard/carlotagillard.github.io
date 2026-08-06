# carlotagillard.github.io

Personal engineering portfolio, live at [carlotagillard.github.io](https://carlotagillard.github.io).

Built with Jekyll on GitHub Pages using a customised version of the Cayman theme.
No build step: pushing to `main` publishes the site.

## Structure

- _config.yml site title, description, theme
- index.md home page
- about.md about page
- projects/ one file per project
- assets/css/style.scss all custom styling
- images/ one subfolder per project

## Adding a project

1. Create `projects/name.md` with front matter:
layout: default
title: Project Name
2. Add images to `images/name/`. Lowercase, hyphenated, no spaces.
3. Link it from `index.md` as `/projects/name.html`, not `.md`.

## Styling

All customisation lives in `assets/css/style.scss`, below the theme import.
Colours are defined once as variables at the top.

Layout classes available in any page:

| Class | Use |
|---|---|
| `figure-center` | one centred image |
| `figure-row` | two images side by side, stacks on mobile |
| `figure-side` | image beside a block of text |
| `button-row` + `resource-link` | grid of link buttons |

To hide the banner subtitle or resize the title on a single page, add a `<style>`
block after the front matter.

## Notes

- Filenames and paths are case-sensitive on GitHub Pages
- Use `/images/...` not `../images/...`
- Photos should be JPEG and under ~300 KB
