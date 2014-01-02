<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true"
    CodeBehind="Categories.aspx.cs" Inherits="SapphireForum.Application.Categories" %>

<asp:Content ID="ContentCategories" ContentPlaceHolderID="MainContent" runat="server">
    <div class="page-header">
        <h1>Categories</h1>
    </div>
    <asp:ListView ID="ListViewCategories" ItemType="SapphireForum.Application.Models.CategoryDTO" runat="server"
        SelectMethod="RepeaterCategories_GetData">
        <LayoutTemplate>
            <table class="table table-hover" runat="server">
                <thead>
                    <tr runat="server">
                        <th runat="server">Name</th>
                        <th runat="server">Total Posts</th>
                        <th runat="server">Description</th>
                    </tr>
                </thead>
                <tbody>
                    <tr runat="server" id="itemPlaceholder">
                    </tr>
                </tbody>
            </table>
        </LayoutTemplate>
        <ItemTemplate>
            <tr runat="server">
                <td runat="server">
                    <asp:LinkButton CssClass="btn btn-link" runat="server"
                        OnCommand="RedirectToPosts_Click"
                        Text="<%#: Item.Name%>" CommandArgument="<%#: Item.Name %>" />
                </td>
                <td runat="server"><span class="badge badge-inverse"><%#: Item.PostsCount %></span></td>
                <td runat="server"><%#: Item.Description%></td>
            </tr>
        </ItemTemplate>
        <EmptyDataTemplate>
            <div class="alert alert-block alert-error">
                <p>Categories data not found...</p>
            </div>
        </EmptyDataTemplate>
    </asp:ListView>
    <asp:DataPager ID="DataPagerPosts" ClientIDMode="Static" runat="server" PagedControlID="ListViewCategories"
        PageSize="3">
        <Fields>
            <asp:NextPreviousPagerField ButtonCssClass="btn btn-link" ShowFirstPageButton="True" ShowNextPageButton="False" />
            <asp:NumericPagerField />
            <asp:NextPreviousPagerField ButtonCssClass="btn btn-link" ShowLastPageButton="True" ShowPreviousPageButton="False" />
        </Fields>
    </asp:DataPager>
</asp:Content>
