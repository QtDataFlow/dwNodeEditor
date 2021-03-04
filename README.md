# dwNodeEditor

## Screenshots

[screenshot](./screenshot1.png)

[screenshot](./screenshot2.png)

## Ideas

WindowFlags: should it be set on call to setWidget anyway?
is inheriting from proxy widget a good design idea?

## Tips

- if a title is set for a title bar, you maybe want to ensure that the NodeItem is wide enough

## Problems

solved: resizeEvent - widget resize does not updatePosition of NodeItem correctly. But updatePosition seems to be called. Maybe value of widget is only updated after move? But shouldn't it then at least match at the end of  moving.
