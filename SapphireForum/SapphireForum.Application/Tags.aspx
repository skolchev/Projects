<%@ Page Title="Tags" Language="C#" MasterPageFile="~/Site.Master"
    AutoEventWireup="true" CodeBehind="Tags.aspx.cs" Inherits="SapphireForum.Application.Tags" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <ul class="nav nav-pills nav-stacked">
        <asp:Repeater ID="TagsRepeater" runat="server" SelectMethod="TagsRepeater_GetData" ItemType="SapphireForum.Application.Models.TagDTO">
            <HeaderTemplate>
                <h3>Most Popular Tags</h3>
            </HeaderTemplate>
            <ItemTemplate>
                <li>
                    <asp:LinkButton ID="TagLinkButton" runat="server"
                        CommandName="Tag"
                        CommandArgument="<%#: Item.Text %>"
                        OnCommand="TagLinkButton_Command" >
                        <%#: Item.PostsCount + " x " + Item.Text %>
                    </asp:LinkButton>
                </li>
            </ItemTemplate>
        </asp:Repeater>
    </ul>
</asp:Content>
