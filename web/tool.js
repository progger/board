function isOutside(e, parent)
{
  var relatedTarget = e.relatedTarget;
  while (relatedTarget && relatedTarget !== parent)
    relatedTarget = relatedTarget.parentNode;
  return !relatedTarget;
};

function getTranslateAttr(x, y)
{
    return "translate(" + x + " " + y + ")";
}
